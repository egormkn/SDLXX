#include <SDL_events.h>
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
    CoreApi core_api(CoreApi::Flag::VIDEO);
    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    ImageApi image_api(ImageApi::Flag::PNG);

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    Window window("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, Window::Flag::SHOWN);

    Renderer renderer(window, Renderer::Flag::ACCELERATED);
    renderer.SetDrawColor(Color::WHITE);

    Texture colors = ImageTexture(renderer, "colors.png");

    Event e;
    bool quit = false;

    uint8_t r = 255, g = 255, b = 255;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_q:
              r += 32;
              break;
            case SDLK_w:
              g += 32;
              break;
            case SDLK_e:
              b += 32;
              break;
            case SDLK_a:
              r -= 32;
              break;
            case SDLK_s:
              g -= 32;
              break;
            case SDLK_d:
              b -= 32;
              break;
          }
        }
      }

      renderer.SetDrawColor(Color::WHITE);
      renderer.Clear();

      colors.SetColorModulation({r, g, b});
      renderer.Copy(colors);

      renderer.Render();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
