const std = @import("std");

const ts = @cImport(
    @cInclude("tree_sitter/api.h"),
);

extern fn tree_sitter_eth_serializer() *ts.TSLanguage;

var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = gpa.allocator();

const NodeType = enum {
    unknown,
    source,
    type,
    // Container types
    slice,
    array,
    @"struct",
    // Base types
    byte,
    uint32,
    uint64,
    int32,
    int64,
    string,
};

const source_code = "{name0:uint64 name1:[uint32 uint32]}";

pub fn main() !void {
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

    const value = try handleType(&cursor);

    var writer = std.ArrayList(u8).init(allocator);
    defer writer.deinit();

    try std.json.stringify(value, .{}, writer.writer());

    std.debug.print("{s}\n", .{writer.items});
}

fn handleStruct(cursor: *ts.TSTreeCursor) error{ UnexpectedNode, OutOfMemory }!std.json.Value {
    const node = ts.ts_tree_cursor_current_node(cursor);
    const n_children = ts.ts_node_child_count(node);

    std.debug.print("array children: {d}\n", .{n_children});

    var result = std.json.ObjectMap.init(allocator);

    if (!ts.ts_tree_cursor_goto_first_child(cursor)) {
        return error.UnexpectedNode;
    }

    for (0..n_children / 4) |_| {
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

        const value = try handleType(cursor);

        try result.put(source_code[key_start..key_end], value);
    }

    _ = ts.ts_tree_cursor_goto_parent(cursor);

    return .{ .object = result };
}

fn handleArray(cursor: *ts.TSTreeCursor) !std.json.Value {
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

        const value = try handleType(cursor);

        try result.append(value);
    }

    _ = ts.ts_tree_cursor_goto_parent(cursor);

    return .{ .array = result };
}

fn handleType(cursor: *ts.TSTreeCursor) error{ UnexpectedNode, OutOfMemory }!std.json.Value {
    const node = ts.ts_tree_cursor_current_node(cursor);
    const node_type = std.mem.span(ts.ts_node_type(node));

    std.debug.print("type: {s}\n", .{node_type});

    switch (std.meta.stringToEnum(NodeType, node_type) orelse .unknown) {
        .byte => return .{ .string = "byte" },
        .uint32 => return .{ .string = "uint32" },
        .uint64 => return .{ .string = "uint64" },
        .int32 => return .null,
        .int64 => return .null,
        .string => return .null,
        .@"struct" => return handleStruct(cursor),
        .array => return handleArray(cursor),
        .type => {
            if (ts.ts_tree_cursor_goto_first_child(cursor)) {
                defer _ = ts.ts_tree_cursor_goto_parent(cursor);

                return try handleType(cursor);
            }

            return error.UnexpectedNode;
        },
        else => return error.UnexpectedNode,
    }

    unreachable;
}

// fn handleStruct(cursor: *ts.TSCursor)
