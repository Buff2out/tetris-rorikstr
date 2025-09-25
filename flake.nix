{
  description = "C Project with Check, Valgrind, Gcov support";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};

      buildInputs = with pkgs; [
        check         # для unit-тестов
        valgrind      # для проверки утечек
        lcov          # для отчетов gcov
        clang-tools   # clang-format
        gcc           # компилятор
        gnumake       # make
        ncurses       # для TUI/CLI приложений
        readline      # для readline поддержки
        zlib          # сжатие данных
        libxml2       # XML parsing
        curl          # HTTP клиент
        openssl       # криптография
        sqlite        # база данных
      ];
    in {
      devShells.default = pkgs.mkShell {
        inherit buildInputs;

        shellHook = ''
          echo "✅ C Project Dev Environment Loaded"
          echo "🔧 Available tools:"
          echo "   - gcc, make, clang-format"
          echo "   - checkmk, valgrind, lcov"
          echo "🚀 Run 'make test' to build and run tests"
        '';
      };
    });
}
