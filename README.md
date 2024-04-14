# ETH Serializer (WIP)

Deserialize byte strings into JSON using a defined structure.

## Usage

It doesn't work yet, but this is the goal:

Example with `BeaconBlockHeader`

```sh
$ ./es 'ssz_decode({slot: uint64 proposerIndex: uint256 parentRoot: uint256 stateRoot: uint256 bodyRoot: uint256})' '0x871a821a158b1cb27a12444fce005658101ffae7ac89e539949774fc138a1831'
{
  slot: 3,
  proposerIndex: 2,
  parentRoot: "0x41485c23d68c1f592677d77c034ad2256f88b1220af2e105fa966baeae9a87b9",
  stateRoot: "0xcbcd6d7f1f0bde6c8ad85efc3941ed5fc0f1663f1adf03209c07e471186adaf8",
  bodyRoot: "0xeaeb8b1728c07a9fb10ad2b61aa2ce8f1b4a17dfab81db49a9729ad1cdbbac40"
}
```

Current working example:

```sh
# Hard coded values:
# source_code = "ssz({slot:uint64 proposerIndex:uint64 parentRoot:uint256 stateRoot:uint256 bodyRoot:uint256})";
# raw_data = "0300000000000000020000000000000041485c23d68c1f592677d77c034ad2256f88b1220af2e105fa966baeae9a87b9cbcd6d7f1f0bde6c8ad85efc3941ed5fc0f1663f1adf03209c07e471186adaf8eaeb8b1728c07a9fb10ad2b61aa2ce8f1b4a17dfab81db49a9729ad1cdbbac40";
$ zig build run
{
  "slot": "3",
  "proposerIndex": "2",
  "parentRoot": "0xb9879aaeae6b96fa05e1f20a22b1886f25d24a037cd77726591f8cd6235c4841",
  "stateRoot": "0xf8da6a1871e4079c2003df1a3f66f1c05fed4139fc5ed88a6cde0b1f7f6dcdcb",
  "bodyRoot": "0x40acbbcdd19a72a949db81abdf174a1b8fcea21ab6d20ab19f7ac028178bebea"
}
```

## Roadmap

- [x] DSL defined in tree-sitter
- [x] DSL Parser:
  - [x] Basic types
  - [x] Arrays
  - [x] Structs
  - [ ] Functions
- [x] Output JSON
- [ ] Webapp with same functionality as CLI
