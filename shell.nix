{ nixpkgs ? import <nixpkgs> {} }:
let
  inherit (nixpkgs) pkgs;

  nixPackages = [
    pkgs.hello pkgs.lcov pkgs.python27
  ];
in
pkgs.stdenv.mkDerivation {
  name = "env";
  buildInputs = nixPackages;
}
