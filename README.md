# SDLXX

[![Build](https://github.com/egormkn/SDLXX/actions/workflows/build.yml/badge.svg)](https://github.com/egormkn/SDLXX/actions/workflows/build.yml)

## Description

SDLXX is a library that implements a modern C++ interface 
to the widely used [SDL](https://www.libsdl.org/) library 
and its extensions: 
[SDL_image](https://www.libsdl.org/projects/SDL_image/), 
[SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/), 
[SDL_net](https://www.libsdl.org/projects/SDL_net/), 
[SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/).

It is designed to provide safe access to audio, keyboard, mouse, joystick, network and graphics hardware.

## Features

- Provides type-safe bindings to SDL2 and its extension libraries
- Uses [RAII idiom](https://en.cppreference.com/w/cpp/language/raii) and C++ smart pointers for safe management of SDL resources
- Supports [vcpkg manifest mode](https://github.com/microsoft/vcpkg/blob/master/docs/users/manifests.md)

## Examples

Here is an example of the [game](https://github.com/egormkn/SDLXX/releases) created using SDLXX:

![Game screenshot](examples/game/data/game.png)

## Alternatives

There are some other projects on Github that aim to provide a similar functionality:

- [libSDL2pp](https://github.com/libSDL2pp/libSDL2pp)
- [sdl++](https://github.com/tcbrindle/sdlxx)

## Development

1) Clone the repository with vcpkg submodule:

```bash
git clone --recurse-submodules https://github.com/egormkn/SDLXX.git
```

2) Open a project in IDE (VSCode/CLion/QtCreator/...) or use CMake to build from command line:

```bash
cd SDLXX
cmake -S . -B build
cmake --build build
```

## License

This library is distributed under the terms of the [ZLib License](LICENSE.md).
