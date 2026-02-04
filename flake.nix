{
  description = "Modern C++ and Documentation environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      # Define supported systems
      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      # Helper to generate an attrset '{ x86_64-linux = f "x86_64-linux"; ... }'
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
    in
    {
      devShells = forAllSystems (
        system:
        let
          pkgs = import nixpkgs { inherit system; };
          # Using Clang as the primary toolchain for better LSP (clangd) support
          stdenv = pkgs.clangStdenv;
        in
        {
          default = pkgs.mkShell.override { inherit stdenv; } {
            # nativeBuildInputs: Tools that run on the host (Compilers, LSPs)
            nativeBuildInputs = with pkgs; [
              # --- C++ Development ---
              clang-tools # clangd, clang-format, clang-tidy
              gdb # Debugger
              gnumake # For your generic Makefile

              # --- Documentation & Markdown ---
              marksman # Markdown LSP
              markdownlint-cli2 # Faster linter
              pandoc # Document converter

              # --- LaTeX (Optimized bundle) ---
              # scheme-small includes most things needed for school/DSA reports
              texliveSmall
            ];
          };
        }
      );
    };
}
