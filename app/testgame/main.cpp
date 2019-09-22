#include <sdlxx/core/SDLXX.h>
#include <sdlxx/image/SDLXX_image.h>
#include <sdlxx/net/SDLXX_net.h>
#include <sdlxx/ttf/SDLXX_ttf.h>
#include <sdlxx/mixer/SDLXX_mixer.h>
#include <sdlxx/core/Window.h>
#include <sdlxx/core/SceneManager.h>
#include "Menu.h"

using namespace SDLXX;

int main(int argc, char *args[]) {
    try {

        SDL sdl(SDL_INIT_VIDEO);
        sdl.setHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        SDL_image sdl_image(IMG_INIT_PNG | IMG_INIT_JPG);
        SDL_mixer sdl_mixer(0/*MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG*/);
        SDL_net sdl_net;
        SDL_ttf sdl_ttf;

#ifndef SDLXX_RELEASE
        sdl.printDebugInfo();
#endif

        Window window("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        Renderer renderer = window.setRenderer(-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        renderer.setColor(Color(0xFFFFFFFF));
        //SDL_RenderSetLogicalSize(renderer.getSDLRenderer(), 800, 600);

        SceneManager manager(window);
        manager.push(new Menu("MENU", window));
        manager.run();

    } catch (std::exception &e) {
        Log::error(e.what());
    }

    return 0;
}
