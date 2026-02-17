{
  description = "Modern C++ and Documentation environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
    in
    {
      devShells = forAllSystems (
        system:
        let
          pkgs = import nixpkgs { inherit system; };

          cpprun = pkgs.writeShellScriptBin "cpprun" ''
            if [ -z "$1" ]; then
              echo "Usage: cpprun <file.cpp>"
              exit 1
            fi
            file="$1"
            base="''${file%.*}"
            echo "--- Compiling $file ---"
            # We use pkgs.gcc directly to ensure the right compiler is used
            ${pkgs.gcc}/bin/g++ -Wall -Wextra -std=c++20 -O2 "$file" -o "$base" && {
              echo "--- Running $base ---"
              ./"$base"
              rm -f "$base"
            } || {
              echo "--- Compilation Failed ---"
              exit 1
            }
          '';
        in
        {
          default = pkgs.mkShell {
            packages = [
              cpprun
              pkgs.gcc
              pkgs.clang-tools
              pkgs.gdb
              pkgs.marksman
              pkgs.markdownlint-cli2
              pkgs.pandoc
              (pkgs.texlive.combine {
                inherit (pkgs.texlive) scheme-medium framed fvextra;
              })
            ];

            shellHook = ''
              export CPATH="${pkgs.clang-tools}/resource-root/include:$CPATH"
            '';
          };
        }
      );
    };
}
