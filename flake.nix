{
  description = "A simple Lua HTTPS module using native platform backends where applicable.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
        stdenv = pkgs.stdenv;
        lib = pkgs.lib;
        luaHttpsPackage = stdenv.mkDerivation {
          name = "lua-https";
          # version = "0.0.0";
          src = ./.;
          nativeBuildInputs = with pkgs; [ cmake ];
          buildInputs = with pkgs; [
            lua curl
          ];
          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=Release"
          ];
          makeTarget = "install";
          meta = {
            description = "A simple Lua HTTPS module using native platform backends where applicable.";
            license = lib.licenses.zlib;
            maintainers = [  ];
          };
        };
      in {
        packages = {
          default = luaHttpsPackage;
          lua-https = luaHttpsPackage;
        };
      }
    );
}
