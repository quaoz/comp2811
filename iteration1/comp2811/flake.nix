{
  description = "COMP2811 coursework 3";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    pre-commit-hooks.url = "github:cachix/git-hooks.nix";
    systems.url = "github:nix-systems/default";
    flake-utils = {
      url = "github:numtide/flake-utils";
      inputs.systems.follows = "systems";
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    pre-commit-hooks,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        checks = {
          pre-commit-check = pre-commit-hooks.lib.${system}.run {
            src = ./.;
            hooks = {
              flake-checker.enable = true;
              clang-format.enable = true;
              convco.enable = true;
            };
          };
        };

        devShells.default = pkgs.mkShell {
          inherit (self.checks.${system}.pre-commit-check) shellHook;
          buildInputs = self.checks.${system}.pre-commit-check.enabledPackages;

          inputsFrom = [self.packages.${system}.default];
        };

        packages.default = pkgs.stdenv.mkDerivation {
          name = "quaketool";
          version = "1.0";

          src = ./.;

          nativeBuildInputs = with pkgs; [
            cmake
            qt6.wrapQtAppsHook
          ];

          buildInputs = with pkgs; [
            qt6.qtbase
            qt6.qtcharts
            qt6.qtwebview
            qt6.qtlocation
            qt6.qtpositioning
            qt6.qtmultimedia
          ];
        };
      }
    );
}
