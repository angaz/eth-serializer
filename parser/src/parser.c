#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 29
#define LARGE_STATE_COUNT 9
#define SYMBOL_COUNT 26
#define ALIAS_COUNT 0
#define TOKEN_COUNT 16
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 4
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 7

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_LBRACE = 2,
  anon_sym_COLON = 3,
  anon_sym_RBRACE = 4,
  anon_sym_LBRACK = 5,
  anon_sym_RBRACK = 6,
  anon_sym_byte = 7,
  anon_sym_uint32 = 8,
  anon_sym_uint64 = 9,
  anon_sym_int32 = 10,
  anon_sym_int64 = 11,
  anon_sym_string = 12,
  anon_sym_LPAREN = 13,
  anon_sym_RPAREN = 14,
  sym_number = 15,
  sym_source = 16,
  sym__expression = 17,
  sym_struct = 18,
  sym_array = 19,
  sym_slice = 20,
  sym_type = 21,
  sym__type = 22,
  sym_function = 23,
  aux_sym_struct_repeat1 = 24,
  aux_sym_array_repeat1 = 25,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_LBRACE] = "{",
  [anon_sym_COLON] = ":",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_byte] = "byte",
  [anon_sym_uint32] = "uint32",
  [anon_sym_uint64] = "uint64",
  [anon_sym_int32] = "int32",
  [anon_sym_int64] = "int64",
  [anon_sym_string] = "string",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_number] = "number",
  [sym_source] = "source",
  [sym__expression] = "_expression",
  [sym_struct] = "struct",
  [sym_array] = "array",
  [sym_slice] = "slice",
  [sym_type] = "type",
  [sym__type] = "_type",
  [sym_function] = "function",
  [aux_sym_struct_repeat1] = "struct_repeat1",
  [aux_sym_array_repeat1] = "array_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_byte] = anon_sym_byte,
  [anon_sym_uint32] = anon_sym_uint32,
  [anon_sym_uint64] = anon_sym_uint64,
  [anon_sym_int32] = anon_sym_int32,
  [anon_sym_int64] = anon_sym_int64,
  [anon_sym_string] = anon_sym_string,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_number] = sym_number,
  [sym_source] = sym_source,
  [sym__expression] = sym__expression,
  [sym_struct] = sym_struct,
  [sym_array] = sym_array,
  [sym_slice] = sym_slice,
  [sym_type] = sym_type,
  [sym__type] = sym__type,
  [sym_function] = sym_function,
  [aux_sym_struct_repeat1] = aux_sym_struct_repeat1,
  [aux_sym_array_repeat1] = aux_sym_array_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_byte] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_string] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_source] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym_struct] = {
    .visible = true,
    .named = true,
  },
  [sym_array] = {
    .visible = true,
    .named = true,
  },
  [sym_slice] = {
    .visible = true,
    .named = true,
  },
  [sym_type] = {
    .visible = true,
    .named = true,
  },
  [sym__type] = {
    .visible = false,
    .named = true,
  },
  [sym_function] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_struct_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_array_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_keytype = 1,
  field_length = 2,
  field_name = 3,
  field_type = 4,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_keytype] = "keytype",
  [field_length] = "length",
  [field_name] = "name",
  [field_type] = "type",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 3},
  [4] = {.index = 6, .length = 5},
  [5] = {.index = 11, .length = 4},
  [6] = {.index = 15, .length = 3},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_name, 0},
  [1] =
    {field_length, 1},
    {field_type, 3},
  [3] =
    {field_keytype, 2},
    {field_keytype, 3},
    {field_name, 1},
  [6] =
    {field_keytype, 2},
    {field_keytype, 3},
    {field_keytype, 4, .inherited = true},
    {field_name, 1},
    {field_name, 4, .inherited = true},
  [11] =
    {field_keytype, 0, .inherited = true},
    {field_keytype, 1, .inherited = true},
    {field_name, 0, .inherited = true},
    {field_name, 1, .inherited = true},
  [15] =
    {field_keytype, 1},
    {field_keytype, 2},
    {field_name, 0},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(1);
      if (lookahead == '(') ADVANCE(7);
      if (lookahead == ')') ADVANCE(8);
      if (lookahead == ':') ADVANCE(3);
      if (lookahead == '[') ADVANCE(5);
      if (lookahead == ']') ADVANCE(6);
      if (lookahead == '{') ADVANCE(2);
      if (lookahead == '}') ADVANCE(4);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(10);
      END_STATE();
    case 1:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 2:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 3:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 4:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 5:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(10);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (lookahead == 'b') ADVANCE(1);
      if (lookahead == 'i') ADVANCE(2);
      if (lookahead == 's') ADVANCE(3);
      if (lookahead == 'u') ADVANCE(4);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'y') ADVANCE(5);
      END_STATE();
    case 2:
      if (lookahead == 'n') ADVANCE(6);
      END_STATE();
    case 3:
      if (lookahead == 't') ADVANCE(7);
      END_STATE();
    case 4:
      if (lookahead == 'i') ADVANCE(8);
      END_STATE();
    case 5:
      if (lookahead == 't') ADVANCE(9);
      END_STATE();
    case 6:
      if (lookahead == 't') ADVANCE(10);
      END_STATE();
    case 7:
      if (lookahead == 'r') ADVANCE(11);
      END_STATE();
    case 8:
      if (lookahead == 'n') ADVANCE(12);
      END_STATE();
    case 9:
      if (lookahead == 'e') ADVANCE(13);
      END_STATE();
    case 10:
      if (lookahead == '3') ADVANCE(14);
      if (lookahead == '6') ADVANCE(15);
      END_STATE();
    case 11:
      if (lookahead == 'i') ADVANCE(16);
      END_STATE();
    case 12:
      if (lookahead == 't') ADVANCE(17);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_byte);
      END_STATE();
    case 14:
      if (lookahead == '2') ADVANCE(18);
      END_STATE();
    case 15:
      if (lookahead == '4') ADVANCE(19);
      END_STATE();
    case 16:
      if (lookahead == 'n') ADVANCE(20);
      END_STATE();
    case 17:
      if (lookahead == '3') ADVANCE(21);
      if (lookahead == '6') ADVANCE(22);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(anon_sym_int32);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(anon_sym_int64);
      END_STATE();
    case 20:
      if (lookahead == 'g') ADVANCE(23);
      END_STATE();
    case 21:
      if (lookahead == '2') ADVANCE(24);
      END_STATE();
    case 22:
      if (lookahead == '4') ADVANCE(25);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_string);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_uint32);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_uint64);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 0},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_byte] = ACTIONS(1),
    [anon_sym_uint32] = ACTIONS(1),
    [anon_sym_uint64] = ACTIONS(1),
    [anon_sym_int32] = ACTIONS(1),
    [anon_sym_int64] = ACTIONS(1),
    [anon_sym_string] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
  },
  [1] = {
    [sym_source] = STATE(26),
    [sym__expression] = STATE(25),
    [sym_struct] = STATE(10),
    [sym_array] = STATE(10),
    [sym_slice] = STATE(10),
    [sym_type] = STATE(25),
    [sym__type] = STATE(10),
    [sym_function] = STATE(25),
    [sym_identifier] = ACTIONS(3),
    [anon_sym_LBRACE] = ACTIONS(5),
    [anon_sym_LBRACK] = ACTIONS(7),
    [anon_sym_byte] = ACTIONS(9),
    [anon_sym_uint32] = ACTIONS(9),
    [anon_sym_uint64] = ACTIONS(9),
    [anon_sym_int32] = ACTIONS(9),
    [anon_sym_int64] = ACTIONS(9),
    [anon_sym_string] = ACTIONS(9),
  },
  [2] = {
    [sym__expression] = STATE(6),
    [sym_struct] = STATE(10),
    [sym_array] = STATE(10),
    [sym_slice] = STATE(10),
    [sym_type] = STATE(6),
    [sym__type] = STATE(10),
    [sym_function] = STATE(6),
    [aux_sym_array_repeat1] = STATE(6),
    [sym_identifier] = ACTIONS(3),
    [anon_sym_LBRACE] = ACTIONS(5),
    [anon_sym_LBRACK] = ACTIONS(7),
    [anon_sym_RBRACK] = ACTIONS(11),
    [anon_sym_byte] = ACTIONS(9),
    [anon_sym_uint32] = ACTIONS(9),
    [anon_sym_uint64] = ACTIONS(9),
    [anon_sym_int32] = ACTIONS(9),
    [anon_sym_int64] = ACTIONS(9),
    [anon_sym_string] = ACTIONS(9),
    [sym_number] = ACTIONS(13),
  },
  [3] = {
    [sym__expression] = STATE(3),
    [sym_struct] = STATE(10),
    [sym_array] = STATE(10),
    [sym_slice] = STATE(10),
    [sym_type] = STATE(3),
    [sym__type] = STATE(10),
    [sym_function] = STATE(3),
    [aux_sym_array_repeat1] = STATE(3),
    [sym_identifier] = ACTIONS(15),
    [anon_sym_LBRACE] = ACTIONS(18),
    [anon_sym_LBRACK] = ACTIONS(21),
    [anon_sym_RBRACK] = ACTIONS(24),
    [anon_sym_byte] = ACTIONS(26),
    [anon_sym_uint32] = ACTIONS(26),
    [anon_sym_uint64] = ACTIONS(26),
    [anon_sym_int32] = ACTIONS(26),
    [anon_sym_int64] = ACTIONS(26),
    [anon_sym_string] = ACTIONS(26),
    [anon_sym_RPAREN] = ACTIONS(24),
  },
  [4] = {
    [sym__expression] = STATE(5),
    [sym_struct] = STATE(10),
    [sym_array] = STATE(10),
    [sym_slice] = STATE(10),
    [sym_type] = STATE(5),
    [sym__type] = STATE(10),
    [sym_function] = STATE(5),
    [aux_sym_array_repeat1] = STATE(5),
    [sym_identifier] = ACTIONS(3),
    [anon_sym_LBRACE] = ACTIONS(5),
    [anon_sym_LBRACK] = ACTIONS(7),
    [anon_sym_byte] = ACTIONS(9),
    [anon_sym_uint32] = ACTIONS(9),
    [anon_sym_uint64] = ACTIONS(9),
    [anon_sym_int32] = ACTIONS(9),
    [anon_sym_int64] = ACTIONS(9),
    [anon_sym_string] = ACTIONS(9),
    [anon_sym_RPAREN] = ACTIONS(29),
  },
  [5] = {
    [sym__expression] = STATE(3),
    [sym_struct] = STATE(10),
    [sym_array] = STATE(10),
    [sym_slice] = STATE(10),
    [sym_type] = STATE(3),
    [sym__type] = STATE(10),
    [sym_function] = STATE(3),
    [aux_sym_array_repeat1] = STATE(3),
    [sym_identifier] = ACTIONS(3),
    [anon_sym_LBRACE] = ACTIONS(5),
    [anon_sym_LBRACK] = ACTIONS(7),
    [anon_sym_byte] = ACTIONS(9),
    [anon_sym_uint32] = ACTIONS(9),
    [anon_sym_uint64] = ACTIONS(9),
    [anon_sym_int32] = ACTIONS(9),
    [anon_sym_int64] = ACTIONS(9),
    [anon_sym_string] = ACTIONS(9),
    [anon_sym_RPAREN] = ACTIONS(31),
  },
  [6] = {
    [sym__expression] = STATE(3),
    [sym_struct] = STATE(10),
    [sym_array] = STATE(10),
    [sym_slice] = STATE(10),
    [sym_type] = STATE(3),
    [sym__type] = STATE(10),
    [sym_function] = STATE(3),
    [aux_sym_array_repeat1] = STATE(3),
    [sym_identifier] = ACTIONS(3),
    [anon_sym_LBRACE] = ACTIONS(5),
    [anon_sym_LBRACK] = ACTIONS(7),
    [anon_sym_RBRACK] = ACTIONS(33),
    [anon_sym_byte] = ACTIONS(9),
    [anon_sym_uint32] = ACTIONS(9),
    [anon_sym_uint64] = ACTIONS(9),
    [anon_sym_int32] = ACTIONS(9),
    [anon_sym_int64] = ACTIONS(9),
    [anon_sym_string] = ACTIONS(9),
  },
  [7] = {
    [sym__expression] = STATE(21),
    [sym_struct] = STATE(10),
    [sym_array] = STATE(10),
    [sym_slice] = STATE(10),
    [sym_type] = STATE(21),
    [sym__type] = STATE(10),
    [sym_function] = STATE(21),
    [sym_identifier] = ACTIONS(3),
    [anon_sym_LBRACE] = ACTIONS(5),
    [anon_sym_LBRACK] = ACTIONS(7),
    [anon_sym_byte] = ACTIONS(9),
    [anon_sym_uint32] = ACTIONS(9),
    [anon_sym_uint64] = ACTIONS(9),
    [anon_sym_int32] = ACTIONS(9),
    [anon_sym_int64] = ACTIONS(9),
    [anon_sym_string] = ACTIONS(9),
  },
  [8] = {
    [sym__expression] = STATE(18),
    [sym_struct] = STATE(10),
    [sym_array] = STATE(10),
    [sym_slice] = STATE(10),
    [sym_type] = STATE(18),
    [sym__type] = STATE(10),
    [sym_function] = STATE(18),
    [sym_identifier] = ACTIONS(3),
    [anon_sym_LBRACE] = ACTIONS(5),
    [anon_sym_LBRACK] = ACTIONS(7),
    [anon_sym_byte] = ACTIONS(9),
    [anon_sym_uint32] = ACTIONS(9),
    [anon_sym_uint64] = ACTIONS(9),
    [anon_sym_int32] = ACTIONS(9),
    [anon_sym_int64] = ACTIONS(9),
    [anon_sym_string] = ACTIONS(9),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 5,
    ACTIONS(5), 1,
      anon_sym_LBRACE,
    ACTIONS(7), 1,
      anon_sym_LBRACK,
    STATE(14), 1,
      sym_type,
    STATE(10), 4,
      sym_struct,
      sym_array,
      sym_slice,
      sym__type,
    ACTIONS(35), 6,
      anon_sym_byte,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_string,
  [24] = 2,
    ACTIONS(37), 6,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(39), 7,
      anon_sym_byte,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_string,
      sym_identifier,
  [42] = 2,
    ACTIONS(41), 6,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(43), 7,
      anon_sym_byte,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_string,
      sym_identifier,
  [60] = 2,
    ACTIONS(45), 6,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(47), 7,
      anon_sym_byte,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_string,
      sym_identifier,
  [78] = 2,
    ACTIONS(49), 6,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(51), 7,
      anon_sym_byte,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_string,
      sym_identifier,
  [96] = 2,
    ACTIONS(53), 6,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(55), 7,
      anon_sym_byte,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_string,
      sym_identifier,
  [114] = 2,
    ACTIONS(57), 6,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(59), 7,
      anon_sym_byte,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_string,
      sym_identifier,
  [132] = 2,
    ACTIONS(61), 6,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(63), 7,
      anon_sym_byte,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_string,
      sym_identifier,
  [150] = 2,
    ACTIONS(65), 6,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(67), 7,
      anon_sym_byte,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_string,
      sym_identifier,
  [168] = 3,
    ACTIONS(69), 1,
      sym_identifier,
    ACTIONS(71), 1,
      anon_sym_RBRACE,
    STATE(19), 1,
      aux_sym_struct_repeat1,
  [178] = 3,
    ACTIONS(69), 1,
      sym_identifier,
    ACTIONS(73), 1,
      anon_sym_RBRACE,
    STATE(20), 1,
      aux_sym_struct_repeat1,
  [188] = 3,
    ACTIONS(75), 1,
      sym_identifier,
    ACTIONS(78), 1,
      anon_sym_RBRACE,
    STATE(20), 1,
      aux_sym_struct_repeat1,
  [198] = 1,
    ACTIONS(80), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [203] = 1,
    ACTIONS(82), 1,
      anon_sym_COLON,
  [207] = 1,
    ACTIONS(84), 1,
      anon_sym_RBRACK,
  [211] = 1,
    ACTIONS(86), 1,
      sym_identifier,
  [215] = 1,
    ACTIONS(88), 1,
      ts_builtin_sym_end,
  [219] = 1,
    ACTIONS(90), 1,
      ts_builtin_sym_end,
  [223] = 1,
    ACTIONS(92), 1,
      anon_sym_COLON,
  [227] = 1,
    ACTIONS(94), 1,
      anon_sym_LPAREN,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(9)] = 0,
  [SMALL_STATE(10)] = 24,
  [SMALL_STATE(11)] = 42,
  [SMALL_STATE(12)] = 60,
  [SMALL_STATE(13)] = 78,
  [SMALL_STATE(14)] = 96,
  [SMALL_STATE(15)] = 114,
  [SMALL_STATE(16)] = 132,
  [SMALL_STATE(17)] = 150,
  [SMALL_STATE(18)] = 168,
  [SMALL_STATE(19)] = 178,
  [SMALL_STATE(20)] = 188,
  [SMALL_STATE(21)] = 198,
  [SMALL_STATE(22)] = 203,
  [SMALL_STATE(23)] = 207,
  [SMALL_STATE(24)] = 211,
  [SMALL_STATE(25)] = 215,
  [SMALL_STATE(26)] = 219,
  [SMALL_STATE(27)] = 223,
  [SMALL_STATE(28)] = 227,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [15] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_array_repeat1, 2), SHIFT_REPEAT(28),
  [18] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2), SHIFT_REPEAT(24),
  [21] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2), SHIFT_REPEAT(2),
  [24] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2),
  [26] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_array_repeat1, 2), SHIFT_REPEAT(10),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1),
  [39] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_type, 1),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 2),
  [43] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 2),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 3),
  [47] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 3),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function, 3, .production_id = 1),
  [51] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_function, 3, .production_id = 1),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_slice, 4, .production_id = 2),
  [55] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_slice, 4, .production_id = 2),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function, 4, .production_id = 1),
  [59] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_function, 4, .production_id = 1),
  [61] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct, 5, .production_id = 3),
  [63] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_struct, 5, .production_id = 3),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct, 6, .production_id = 4),
  [67] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_struct, 6, .production_id = 4),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [75] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_struct_repeat1, 2, .production_id = 5), SHIFT_REPEAT(27),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_struct_repeat1, 2, .production_id = 5),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_struct_repeat1, 3, .production_id = 6),
  [82] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source, 1),
  [90] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [92] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_eth_serializer(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
