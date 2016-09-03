# Minesweeper
A minimalist minesweeper game.

Play the web version here: https://theinnerparty.github.io/Minesweeper/webDemo/minesweeper.html

Includes a fully featured and portable game logic engine, and a graphical frontend written with openFrameworks.

## Build Instructions (for macOS):

1. Install openFrameworks, and go to myApps directory.
2. To build desktop version, open with xcode or run
````xcodebuild -project minesweeper.xcodeproj````
3. to build for web (requires emscripten):
````emmake make -j4 && emrun bin/minesweeper.html````

Note: Emscripten related settings in projects makefile cause standard ````make```` to fail. This is a known bug and will be fixed in the future.

## License:
© Leo Dastur. Licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International license.
