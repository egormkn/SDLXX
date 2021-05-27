#include <SDL_events.h>
#include <SDL_render.h>
#include <sdlxx/core/core_api.h>
#include <sdlxx/core/events.h>
#include <sdlxx/core/log.h>
#include <sdlxx/core/renderer.h>
#include <sdlxx/core/surface.h>
#include <sdlxx/core/window.h>
#include <sdlxx/image/image_api.h>
#include <sdlxx/image/image_surface.h>
#include <sdlxx/image/image_texture.h>

using namespace std;
using namespace sdlxx::core;
using namespace sdlxx::image;

int main(int argc, char* args[]) {
  try {
    CoreApi core_api({CoreApi::Flag::VIDEO});
    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    ImageApi image_api({ImageApi::Flag::PNG});

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    Window window("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, {Window::Flag::SHOWN});

    Renderer renderer(window, {Renderer::Flag::ACCELERATED});
    renderer.SetDrawColor(Color::WHITE);

    Texture fadein = ImageTexture(renderer, "fadein.png");
    Texture fadeout = ImageTexture(renderer, "fadeout.png");
    fadeout.SetBlendMode(BlendMode::BLEND);

    Event e;
    bool quit = false;

    uint8_t alpha = 255;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_w:
              alpha = alpha <= 255 - 32 ? alpha + 32 : 255;
              break;
            case SDLK_s:
              alpha = alpha >= 32 ? alpha - 32 : 0;
              break;
          }
        }
      }

      renderer.SetDrawColor(Color::WHITE);
      renderer.Clear();

      renderer.Copy(fadein);

      fadeout.SetAlphaModulation(alpha);
      renderer.Copy(fadeout);

      renderer.Render();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
