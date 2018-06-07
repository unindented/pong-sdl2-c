# Pong clone built with SDL2 in C [![Travis Build Status](https://img.shields.io/travis/unindented/pong-sdl2-c.svg)](http://travis-ci.org/unindented/pong-sdl2-c) [![Appveyor Build Status](https://img.shields.io/appveyor/ci/unindented/pong-sdl2-c.svg)](https://ci.appveyor.com/project/unindented/pong-sdl2-c)

## Prerequisites

### Linux

Install CMake and SDL2 through your package manager. For example, if you're on Ubuntu:

```
sudo apt install build-essential cmake libsdl2{,-mixer,-ttf}-dev
```

You may be able to install Check through your package manager too, although Ubuntu distributes a really old version of Check, so you'll want to build it yourself:

```
cd /tmp
wget https://github.com/libcheck/check/releases/download/0.12.0/check-0.12.0.tar.gz
tar zxf check-0.12.0.tar.gz
cd check-0.12.0
./configure
make
sudo make install
```

### macOS

Install CMake, SDL2, and Check through Homebrew:

```
brew install cmake sdl2{,_mixer,_ttf} check
```

### Windows

Download MinGW:

- 32-bit installation: <https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/6.3.0/threads-posix/seh/x86_64-6.3.0-release-posix-seh-rt_v5-rev2.7z/download>
- 64-bit installation: <https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/6.3.0/threads-posix/seh/x86_64-6.3.0-release-posix-seh-rt_v5-rev2.7z/download>

I'd recommend creating a `MINGW_DIR` environment variable pointing to your MinGW installation, and adding `%MINGW_DIR%\bin` to your `PATH`.

Download SDL2 development libraries:

- <https://www.libsdl.org/release/SDL2-devel-2.0.8-mingw.tar.gz>
- <https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.2-mingw.tar.gz>
- <https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-mingw.tar.gz>

Extract them, and copy the files for your architecture into MinGW's folder.

For a 32-bit installation:

```
xcopy "SDL2-2.0.8\i686-w64-mingw32\*" "%MINGW_DIR%\" /s /y
xcopy "SDL2_mixer-2.0.2\i686-w64-mingw32\*" "%MINGW_DIR%\" /s /y
xcopy "SDL2_ttf-2.0.14\i686-w64-mingw32\*" "%MINGW_DIR%\" /s /y
```

For a 64-bit installation:

```
xcopy "SDL2-2.0.8\x86_64-w64-mingw32\*" "%MINGW_DIR%\" /s /y
xcopy "SDL2_mixer-2.0.2\x86_64-w64-mingw32\*" "%MINGW_DIR%\" /s /y
xcopy "SDL2_ttf-2.0.14\x86_64-w64-mingw32\*" "%MINGW_DIR%\" /s /y
```

Download Check, and have it install into MinGW's folder:

```
cd %TEMP%
wget https://github.com/libcheck/check/releases/download/0.12.0/check-0.12.0.tar.gz
7z x check-0.12.0.tar.gz -so | 7z x -si -ttar -o.
cd check-0.12.0
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="%MINGW_DIR%" -G "MinGW Makefiles" ..
mingw32-make
mingw32-make install
```

## Build

### Linux & macOS

To build the game for release, do:

```
mkdir build
cd build
cmake -DBUILD_ARCH=64 -DCMAKE_BUILD_TYPE=Release ..
make
```

To build the game for debug, specify `CMAKE_BUILD_TYPE=Debug` instead.

### Windows

To build the game for release, do:

```
mkdir build
cd build
cmake -DBUILD_ARCH=64 -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ..
mingw32-make
```

To build the game for debug, specify `CMAKE_BUILD_TYPE=Debug` instead.

## Test

Unit tests are run after build, or through the `test` target.

## Run

Binaries get built into the `build/src` folder.

## Meta

- Code: `git clone https://github.com/unindented/pong-sdl2-c.git`
- Home: <https://unindented.org/>

## Contributors

Daniel Perez Alvarez ([unindented@gmail.com](mailto:unindented@gmail.com))

## License

Copyright (c) 2018 Daniel Perez Alvarez ([unindented.org](https://unindented.org/)). This is free software, and may be redistributed under the terms specified in the LICENSE file.
