{
  description = "Ethereum serialize-deserialize in your browser";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    zig.url = "github:mitchellh/zig-overlay";
    zls.url = "github:zigtools/zls";

    devshell = {
      url = "github:numtide/devshell";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    flake-parts = {
      url = "github:hercules-ci/flake-parts";
    };
    gitignore = {
      url = "github:hercules-ci/gitignore.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = inputs@{
    self,
    nixpkgs,
    devshell,
    flake-parts,
    gitignore,
    ...
  }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      imports = [
        devshell.flakeModule
        flake-parts.flakeModules.easyOverlay
      ];

      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      perSystem = { config, pkgs, system, ... }: let
        inherit (gitignore.lib) gitignoreSource;
        zig = inputs.zig.packages.${system};
        zls = inputs.zls.packages.${system}.zls;
      in {
        overlayAttrs = {
          inherit (config.packages)
            eth_serializer;
        };

        packages = {
          eth_serializer = pkgs.stdenv.mkDerivation {
            pname = "eth_serializer";
            version = "0.0.1";

            src = gitignoreSource ./.;

            nativeBuildInputs = [
              zig.master-2024-03-12
            ];

            buildPhase = ''
              mkdir -p .cache

              ln -s ${pkgs.callPackage ./deps.nix { }} $(pwd)/.cache/p

              zig build \
                --color off \
                --cache-dir $(pwd)/zig-cache \
                --global-cache-dir $(pwd)/.cache \
                --prefix $out

              cp public/* $out
            '';
          };
        };

        devshells.default = {
          packages = with pkgs; [
            gcc
            gnumake
            nodePackages.node-gyp
            nodejs
            tree-sitter

            zon2nix

            zig.master-2024-03-28
            zls
          ];
        };
      };
    };
}
