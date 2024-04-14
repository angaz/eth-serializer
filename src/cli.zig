const std = @import("std");
const ssz = @import("ssz");

const ts = @cImport(
    @cInclude("tree_sitter/api.h"),
);

extern fn tree_sitter_eth_serializer() *ts.TSLanguage;

var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = gpa.allocator();

const NodeType = enum {
    unknown,
    source,
    function,
    type,
    // Container types
    slice,
    array,
    @"struct",
    // Base types
    byte,
    uint32,
    uint64,
    uint128,
    uint256,
    int32,
    int64,
    string,
};

const ParserError = error{
    UnexpectedNode,
    OutOfMemory,
    CursorProgression,
};

const DataReader = struct {
    buffer: []const u8,
    pos: usize,
};

const FunctionType = struct {
    const Type = *const fn (*DataReader) ParserError!std.json.Value;

    u8: Type,
    u64: Type,
    u256: Type,
};

const FunctionNames = enum {
    unknown,
    ssz,
};

const functions = struct {
    const ssz = FunctionType{
        .u8 = struct {
            fn func(data: *DataReader) ParserError!std.json.Value {
                return try ssz_decode(u8, data);
            }
        }.func,
        .u64 = struct {
            fn func(data: *DataReader) ParserError!std.json.Value {
                return try ssz_decode(u64, data);
            }
        }.func,
        .u256 = struct {
            fn func(data: *DataReader) ParserError!std.json.Value {
                return try ssz_decode(u256, data);
            }
        }.func,
    };
};

const source_code = "ssz({slot:uint64 proposerIndex:uint64 parentRoot:uint256 stateRoot:uint256 bodyRoot:uint256})";
const raw_data = "0300000000000000020000000000000041485c23d68c1f592677d77c034ad2256f88b1220af2e105fa966baeae9a87b9cbcd6d7f1f0bde6c8ad85efc3941ed5fc0f1663f1adf03209c07e471186adaf8eaeb8b1728c07a9fb10ad2b61aa2ce8f1b4a17dfab81db49a9729ad1cdbbac40";

pub fn main() !void {
    const data_buff = try allocator.alloc(u8, raw_data.len / 2);

    const data = try std.fmt.hexToBytes(data_buff, raw_data);
    var parser = Parser.init(
        allocator,
        source_code,
        data,
    );
    defer parser.deinit();

    const value = try parser.parse();

    var writer = std.ArrayList(u8).init(allocator);
    defer writer.deinit();

    try std.json.stringify(value, .{ .whitespace = .indent_2 }, writer.writer());

    std.debug.print("{s}\n", .{writer.items});
}

const ParserFn = struct {
    functions: FunctionType,
    node: *const ts.TSNode,
};

const ParserFunctions = std.ArrayList(ParserFn);

const Parser = struct {
    fnStack: ParserFunctions,
    source: []const u8,
    data: DataReader,

    const Self = @This();

    pub fn init(alloc: std.mem.Allocator, source: []const u8, data: []const u8) Self {
        return .{
            .fnStack = ParserFunctions.init(alloc),
            .source = source,
            .data = .{
                .buffer = data,
                .pos = 0,
            },
        };
    }

    pub fn deinit(self: *Self) void {
        self.fnStack.deinit();
    }

    pub fn parse(self: *Self) ParserError!std.json.Value {
        const parser = ts.ts_parser_new();
        defer ts.ts_parser_delete(parser);

        const ok = ts.ts_parser_set_language(
            parser,
            tree_sitter_eth_serializer(),
        );
        if (!ok) {
            std.debug.print("set parser language failed\n", .{});
            std.posix.exit(1);
        }

        const tree = ts.ts_parser_parse_string(
            parser,
            null,
            source_code.ptr,
            source_code.len,
        );
        defer ts.ts_tree_delete(tree);

        const root = ts.ts_tree_root_node(tree);
        const syntax = ts.ts_node_string(root);

        std.debug.print("{s}\n", .{syntax});

        var cursor = ts.ts_tree_cursor_new(root);

        const node = ts.ts_tree_cursor_current_node(&cursor);
        const node_type = std.mem.span(ts.ts_node_type(node));

        if (!std.mem.eql(u8, node_type, "source")) {
            return error.UnexpectedNode;
        }

        if (!ts.ts_tree_cursor_goto_first_child(&cursor)) {
            return error.CursorProgression;
        }

        return self.handleExpression(&cursor);
    }

    fn handleStruct(self: *Self, cursor: *ts.TSTreeCursor) ParserError!std.json.Value {
        const node = ts.ts_tree_cursor_current_node(cursor);
        const n_children = ts.ts_node_child_count(node);

        std.debug.print("struct children: {d}\n", .{n_children});

        var result = std.json.ObjectMap.init(allocator);

        if (!ts.ts_tree_cursor_goto_first_child(cursor)) {
            return error.UnexpectedNode;
        }

        for (0..n_children / 3) |_| {
            // key
            if (!ts.ts_tree_cursor_goto_next_sibling(cursor)) {
                return error.UnexpectedNode;
            }

            const key_node = ts.ts_tree_cursor_current_node(cursor);
            const key_start = ts.ts_node_start_byte(key_node);
            const key_end = ts.ts_node_end_byte(key_node);

            // colon separator
            if (!ts.ts_tree_cursor_goto_next_sibling(cursor)) {
                return error.UnexpectedNode;
            }

            // value
            if (!ts.ts_tree_cursor_goto_next_sibling(cursor)) {
                return error.UnexpectedNode;
            }

            const value = try self.handleExpression(cursor);

            try result.put(self.source[key_start..key_end], value);
        }

        _ = ts.ts_tree_cursor_goto_parent(cursor);

        return .{ .object = result };
    }

    fn handleArray(self: *Self, cursor: *ts.TSTreeCursor) ParserError!std.json.Value {
        const node = ts.ts_tree_cursor_current_node(cursor);
        const n_children = ts.ts_node_child_count(node);

        var result = std.json.Array.init(allocator);

        if (!ts.ts_tree_cursor_goto_first_child(cursor)) {
            return error.UnexpectedNode;
        }

        for (0..n_children / 2) |_| {
            if (!ts.ts_tree_cursor_goto_next_sibling(cursor)) {
                return error.UnexpectedNode;
            }

            const value = try self.handleExpression(cursor);

            try result.append(value);
        }

        _ = ts.ts_tree_cursor_goto_parent(cursor);

        return .{ .array = result };
    }

    fn handleFunction(self: *Self, cursor: *ts.TSTreeCursor) ParserError!std.json.Value {
        // fn name
        if (!ts.ts_tree_cursor_goto_first_child(cursor)) {
            return error.UnexpectedNode;
        }

        const fn_node = ts.ts_tree_cursor_current_node(cursor);
        const fn_start = ts.ts_node_start_byte(fn_node);
        const fn_end = ts.ts_node_end_byte(fn_node);

        const fn_name = self.source[fn_start..fn_end];

        std.debug.print("fn name: {s}\n", .{fn_name});

        const function = switch (std.meta.stringToEnum(FunctionNames, fn_name) orelse .unknown) {
            .ssz => functions.ssz,
            else => return error.UnexpectedNode,
        };

        try self.fnStack.append(.{
            .functions = function,
            .node = &fn_node,
        });

        // open paren
        if (!ts.ts_tree_cursor_goto_next_sibling(cursor)) {
            return error.UnexpectedNode;
        }

        // parameter
        if (!ts.ts_tree_cursor_goto_next_sibling(cursor)) {
            return error.UnexpectedNode;
        }

        const value = try self.handleExpression(cursor);

        _ = self.fnStack.pop();
        _ = ts.ts_tree_cursor_goto_parent(cursor);

        return value;
    }

    fn currentFunction(self: *Self) FunctionType {
        return self.fnStack.getLast().functions;
    }

    fn handleExpression(self: *Self, cursor: *ts.TSTreeCursor) ParserError!std.json.Value {
        const node = ts.ts_tree_cursor_current_node(cursor);
        const node_type = std.mem.span(ts.ts_node_type(node));

        std.debug.print("type: {s}\n", .{node_type});

        switch (std.meta.stringToEnum(NodeType, node_type) orelse .unknown) {
            .byte => return .{ .string = "byte" },
            .uint32 => return .{ .string = "uint32" },
            .uint64 => return try self.currentFunction().u64(&self.data),
            .uint128 => return .{ .string = "uint128" },
            .uint256 => return try self.currentFunction().u256(&self.data),
            .int32 => return .null,
            .int64 => return .null,
            .string => return .null,
            .@"struct" => return try self.handleStruct(cursor),
            .array => return try self.handleArray(cursor),
            .function => return try self.handleFunction(cursor),
            .type => {
                if (ts.ts_tree_cursor_goto_first_child(cursor)) {
                    defer _ = ts.ts_tree_cursor_goto_parent(cursor);

                    return try self.handleExpression(cursor);
                }

                return error.UnexpectedNode;
            },
            else => return error.UnexpectedNode,
        }

        unreachable;
    }
};

fn ssz_decode(comptime T: type, data: *DataReader) !std.json.Value {
    var out: T = undefined;

    const read = try ssz.deserialize(T, data.buffer[data.pos..], &out);
    data.pos += read;

    std.debug.print("read: {d}, value: {d}\n", .{ read, out });

    switch (T) {
        u64 => return .{ .string = try std.fmt.allocPrint(allocator, "{d}", .{out}) },
        u256 => return .{ .string = try std.fmt.allocPrint(allocator, "0x{x}", .{out}) },
        else => return error.UnexpectedNode,
    }
}
