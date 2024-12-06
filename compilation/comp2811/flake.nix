{
  description = "COMP2811 coursework 3";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    systems.url = "github:nix-systems/default";
    flake-utils = {
      url = "github:numtide/flake-utils";
      inputs.systems.follows = "systems";
    };
  };

  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            just
            cmake
            qt6.qtbase
            qt6.qtcharts
            qt6.qtwebview
            qt6.qtlocation
            qt6.qtpositioning
            qt6.qtmultimedia
            libclang.python
          ];
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
