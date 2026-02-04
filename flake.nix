{
  description = "C++ development environment with Clang and CMake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      utils,
    }:
    utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
        # Use a Clang-based standard environment
        stdenv = pkgs.clangStdenv;
      in
      {
        devShells.default = pkgs.mkShell.override { inherit stdenv; } {
          nativeBuildInputs = with pkgs; [
            clang-tools
            gcc
            gnumake
            marksman
            markdownlint-cli
          ];

          shellHook = ''
            echo "C++ Development Shell (Clang)"
            # Generates a compile_commands.json for clangd if using CMake
            export CMAKE_EXPORT_COMPILE_COMMANDS=1
          '';
        };
      }
    );
}
