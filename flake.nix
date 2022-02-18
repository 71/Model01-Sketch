{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShell = pkgs.mkShell {
          shellHook = ''
            alias generate-keymaps='${pkgs.deno}/bin/deno run --allow-read=./README.md --allow-write=./Sketch/Keymaps.h ./generateKeymaps.ts'
            alias arduinocli='${pkgs.arduino-cli}/bin/arduino-cli --additional-urls https://raw.githubusercontent.com/keyboardio/boardsmanager/master/package_keyboardio_index.json'

            arduinocli core update-index
            arduinocli core install keyboardio:avr@1.99.5 arduino:avr

            alias compile-sketch='arduinocli compile --fqbn keyboardio:avr:model01 Sketch/Sketch.ino'
            alias flash-sketch='sudo compile-sketch && echo press escape and wait... && sudo arduinocli upload --fqbn keyboardio:avr:model01 Sketch/Sketch.ino -p'
            alias list-boards='arduinocli board list'

            echo available commands: compile-sketch flash-sketch list-boards
          '';
        };
      }
    );
}
