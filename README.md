# Minesweeper
A minimalist minesweeper game.

Play the web version [here](https://theinnerparty.github.io/Minesweeper/webDemo/minesweeper.html).

Includes a fully featured and portable game logic engine, and a graphical frontend written with openFrameworks.

## Build Instructions (for macOS):

1. Install openFrameworks, and go to myApps directory.
2. To build desktop version, open with xcode or run
````xcodebuild -project minesweeper.xcodeproj````
3. to build for web (requires [emscripten](http://kripken.github.io/emscripten-site/)):
````emmake make -j4 && emrun bin/minesweeper.html````


## License:
© Leo Dastur. Licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International license.
