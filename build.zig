const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.resolveTargetQuery(.{
        .cpu_arch = .wasm32,
        .os_tag = .freestanding,
    });
    const optimize = b.standardOptimizeOption(.{
        .preferred_optimize_mode = .ReleaseSmall,
    });

    const exe = b.addExecutable(.{
        .name = "eth-serializer",
        .root_source_file = .{ .path = "src/root.zig" },
        .target = target,
        .optimize = optimize,
        .strip = false,
    });
    exe.entry = .disabled;
    exe.use_llvm = false;
    exe.use_lld = false;
    exe.root_module.export_symbol_names = &.{
        "add",
    };

    exe.root_module.addImport(
        "zig-rlp",
        b.dependency("zig-rlp", .{
            .target = target,
            .optimize = optimize,
        }).module("rlp"),
    );

    b.getInstallStep().dependOn(makeInstallSiteStep(b, exe));

    b.addRunArtifact()
}

const InstallSiteStep = struct {
    exe: *std.Build.Step.Compile = undefined,

    pub fn installSite(self: *@This(), step: *std.Build.Step, _: *std.Progress.Node) !void {
        const b = step.owner;
        b.installFile("public/index.html", "public/index.html");
        b.installFile("public/eth-serializer.js", "public/eth-serializer.js");

        hashFile(b.exe_dir, self.exe.out_filename) catch |err| {
            std.debug.print(
                "hash file \"{s}\" failed: {s}\n",
                .{
                    "",
                    @errorName(err),
                },
            );

            return;
        };
    }
};

fn makeInstallSiteStep(b: *std.Build, artifact: *std.Build.Step.Compile) *std.Build.Step {
    var installSite = b.allocator.create(InstallSiteStep) catch @panic("OOM");
    installSite.exe = artifact;

    const siteStep = b.step("install site", "Copy HTML, JS files, add hash to filenames");
    siteStep.makeFn = installSite.installSite;
    siteStep.dependOn(&b.addInstallArtifact(artifact, .{}).step);

    return siteStep;
}

fn hashFile(alloc: std.mem.Allocator, in_dir: ?[]const u8, in_filename: []const u8) !void {
    const in = if (in_dir != null) try std.fmt.allocPrint(alloc, "{s}/{s}", .{ in_dir.?, in_filename }) else try alloc.dupe(u8, in_filename);
    defer alloc.free(in);

    std.debug.print("{s}\n", .{in});

    const in_file = try std.os.open(in, .{}, 0o644);
    defer std.os.close(in_file);

    var hash = std.crypto.hash.sha3.Keccak256.init(.{});
    const hash_writer = hash.writer();

    {
        var buf: [8196]u8 = undefined;

        while (true) {
            const n_read = try std.os.read(in_file, &buf);
            if (n_read == 0) {
                break;
            }

            _ = try hash_writer.write(buf[0..n_read]);
        }
    }

    var digest: [32]u8 = undefined;
    _ = hash.final(&digest);

    const extension_index = std.mem.lastIndexOfScalar(u8, in, '.') orelse return error.FILE_WITHOUT_EXTENSION;

    const out_filename = try std.fmt.allocPrint(
        alloc,
        "{s}.{s}{s}",
        .{
            in[0..extension_index],
            std.fmt.fmtSliceHexLower(digest[0..4]),
            in[extension_index..],
        },
    );
    defer alloc.free(out_filename);

    try std.os.rename(in, out_filename);
}
