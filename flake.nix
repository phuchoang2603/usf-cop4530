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

      # This helper now creates pkgs for the system before passing it to your shell config
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
    in
    {
      devShells = forAllSystems (
        system:
        let
          pkgs = import nixpkgs { inherit system; };
        in
        {
          default = pkgs.mkShell {
            packages = [
              # --- C++ Development ---
              pkgs.clang-tools # clangd, clang-format, clang-tidy
              pkgs.gdb # Debugger
              pkgs.gnumake # For your generic Makefile

              # --- Documentation ---
              pkgs.marksman # Markdown LSP
              pkgs.markdownlint-cli2 # Faster linter
              pkgs.pandoc # Document converter

              # --- LaTeX ---
              (pkgs.texlive.combine {
                inherit (pkgs.texlive)
                  scheme-medium
                  framed
                  fvextra # Often required by pandoc for code blocks
                  ;
              })
            ];

            shellHook = ''
              echo "🛡️  C++ DSA & Documentation Shell Loaded"
              # Ensure clangd finds headers on NixOS
              export CPATH="${pkgs.clang-tools}/resource-root/include:$CPATH"
            '';
          };
        }
      );
    };
}
