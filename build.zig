const std = @import("std");

pub fn build(b: *std.Build) void {
    const target_cli = b.standardTargetOptions(.{});
    const optimize_cli = b.standardOptimizeOption(.{});

    const target_wasm = b.resolveTargetQuery(.{
        .cpu_arch = .wasm32,
        .os_tag = .freestanding,
    });
    _ = target_wasm;
    const optimize_wasm = b.standardOptimizeOption(.{
        .preferred_optimize_mode = .ReleaseSmall,
    });
    _ = optimize_wasm;

    const cli = b.addExecutable(.{
        .name = "es",
        .root_source_file = .{ .path = "src/cli.zig" },
        .target = target_cli,
        .optimize = optimize_cli,
    });
    cli.root_module.addImport(
        "rlp",
        b.dependency("zig-rlp", .{
            .target = target_cli,
            .optimize = optimize_cli,
        }).module("rlp"),
    );
    cli.root_module.addImport(
        "ssz",
        b.dependency("ssz.zig", .{
            .target = target_cli,
            .optimize = optimize_cli,
        }).module("ssz"),
    );

    const tree_sitter_dep = b.dependency("tree-sitter", .{
        .target = target_cli,
        .optimize = optimize_cli,
    });

    cli.addIncludePath(tree_sitter_dep.path("lib/include"));
    cli.linkLibrary(tree_sitter_dep.artifact("tree-sitter"));

    cli.addIncludePath(.{ .path = "./parser/src/tree_sitter/" });
    cli.addCSourceFile(.{
        .file = .{ .path = "./parser/src/parser.c" },
    });
    // cli.linkLibC();

    // const wasm = b.addExecutable(.{
    //     .name = "eth-serializer-wasm",
    //     .root_source_file = .{ .path = "src/root.zig" },
    //     .target = target_wasm,
    //     .optimize = optimize_wasm,
    //     .strip = false,
    // });
    // wasm.entry = .disabled;
    // wasm.use_llvm = false;
    // wasm.use_lld = false;
    // wasm.root_module.export_symbol_names = &.{
    //     "add",
    // };

    // wasm.root_module.addImport(
    //     "zig-rlp",
    //     b.dependency("zig-rlp", .{
    //         .target = target_wasm,
    //         .optimize = optimize_wasm,
    //     }).module("rlp"),
    // );

    b.installArtifact(cli);
    // b.installArtifact(wasm);

    // b.getInstallStep().dependOn(makeInstallSiteStep(b, wasm));

    const run_cmd = b.addRunArtifact(cli);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}

const InstallSiteStep = struct {
    const Self = @This();

    exe: *std.Build.Step.Compile,
    step: std.Build.Step,
    owner: *std.Build,

    pub fn create(b: *std.Build, exe: *std.Build.Step.Compile) *Self {
        const self = b.allocator.create(Self) catch @panic("OOM");
        self.* = .{
            .exe = exe,
            .owner = b,
            .step = std.Build.Step.init(.{
                .id = .custom,
                .name = "install site",
                .owner = b,
                .makeFn = make,
            }),
        };

        return self;
    }

    pub fn make(step: *std.Build.Step, _: *std.Progress.Node) !void {
        const self = @fieldParentPtr(Self, "step", step);
        const b = step.owner;

        const bin = self.exe.out_filename;

        // b.installFile("public/index.html", "public/index.html");
        // b.installFile("public/eth-serializer.js", "public/eth-serializer.js");

        hashFile(b.allocator, b.exe_dir, bin) catch |err| {
            std.debug.print(
                "hash file \"{s}\" failed: {s}\n",
                .{ bin, @errorName(err) },
            );

            return;
        };
    }
};

fn makeInstallSiteStep(b: *std.Build, artifact: *std.Build.Step.Compile) *std.Build.Step {
    const installSite = InstallSiteStep.create(b, artifact);

    return &installSite.step;
}

fn hashFile(alloc: std.mem.Allocator, in_dir: ?[]const u8, in_filename: []const u8) !void {
    const in = if (in_dir != null)
        try std.fmt.allocPrint(alloc, "{s}/{s}", .{ in_dir.?, in_filename })
    else
        try alloc.dupe(u8, in_filename);
    defer alloc.free(in);

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
