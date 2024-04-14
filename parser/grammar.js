module.exports = grammar({
  name: 'eth_serializer',

  word: $ => $.identifier,

  rules: {
    source: $ => $._expression,

    _expression: $ => choice(
      $.type,
      $.function,
    ),

    struct: $ => seq(
      '{',
      at_least_one(
        field('keytype', seq(
          field('name', $.identifier),
          ':',
          $._expression,
        )),
      ),
      '}',
    ),

    array: $ => seq(
      '[',
      repeat($._expression),
      ']',
    ),

    slice: $ => seq(
      '[',
      field('length', $.number),
      ']',
      field('type', $.type),
    ),

    type: $ => choice(
      $._type,
      $.slice,
      $.array,
      $.struct,
    ),

    _type: _ => choice(
      'byte',
      'uint32',
      'uint64',
      'uint128',
      'uint256',
      'int32',
      'int64',
      'string',
    ),

    function: $ => seq(
      field('name', $.identifier),
      '(',
      repeat($._expression),
      ')',
    ),

    number: _ => /\d+/,
    identifier: _ => /[a-zA-Z][a-zA-Z0-9_]*/,
  },
});

function at_least_one(rule) {
  return seq(rule, repeat(rule));
}
