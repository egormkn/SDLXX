# SDLXX
A simple and powerful C++ game engine based on SDL2 (+image, net, ttf, mixer) library

Game example ([download here](https://github.com/egormkn/SDLXX/releases))

![Screenshot](resources/game.png)

See also SDL2pp and sdl2-platformer projects

TODO: Write a README :)

## Development

Install IDE (VSCode or CLion preferred), Git, CMake 3.15+, vcpkg

For VSCode: open project and install all suggested VSCode extensions.
Then go to preferences and set these parameters:

```
...
    "C_Cpp.clang_format_fallbackStyle": "Google",
    "C_Cpp.default.configurationProvider": "vector-of-bool.cmake-tools",
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "PATH_TO_VCPKG_CMAKE_TOOLCHAIN_HERE"
    }
...
```

Open CMake panel, right-click SDLXX/app/testgame/SDLXX_game and choose
"Run in terminal".
