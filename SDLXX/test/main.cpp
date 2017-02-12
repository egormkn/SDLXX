#include "../SDLXX.h"
#include "../SDLXX_image.h"
#include "../SDLXX_net.h"
#include "../ttf/SDLXX_ttf.h"
#include "../SDLXX_mixer.h"
#include "../base/Window.h"
#include "../base/SceneManager.h"
#include "Menu.h"

using namespace SDLXX;

int main(int argc, char *args[]) {
    try {

        SDL sdl(SDL_INIT_VIDEO);
        sdl.setHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        SDL_image sdl_image(IMG_INIT_PNG | IMG_INIT_JPG);
        SDL_mixer sdl_mixer(/*MIX_INIT_FLAC | */MIX_INIT_MP3 | MIX_INIT_OGG);
        SDL_net sdl_net;
        SDL_ttf sdl_ttf;

#ifndef SDLXX_RELEASE
        sdl.printDebugInfo();
#endif

        Window window("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        Renderer renderer = window.setRenderer(-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        renderer.setColor(Color(0xFFFFFFFF));

        SceneManager manager(window);
        manager.push(new Menu("MENU", window));
        manager.run();

    } catch (std::exception &e) {
        Log::error(e.what());
    }

    return 0;
}