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

    Renderer renderer(window, Renderer::Flag::ACCELERATED | Renderer::Flag::PRESENTVSYNC);
    renderer.SetDrawColor(Color::WHITE);

    Texture arrow = ImageTexture(renderer, "arrow.png");
    Dimensions arrow_size = arrow.Query().dimensions;

    Event e;
    bool quit = false;

    double angle = 0;
    Renderer::Flip flip = Renderer::Flip::NONE;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_a:
              angle -= 60;
              break;
            case SDLK_s:
              angle = 0;
              flip = Renderer::Flip::NONE;
              break;
            case SDLK_d:
              angle += 60;
              break;
            case SDLK_q:
              flip = Renderer::Flip::HORIZONTAL;
              break;
            case SDLK_w:
              flip = Renderer::Flip::NONE;
              break;
            case SDLK_e:
              flip = Renderer::Flip::VERTICAL;
              break;
          }
        }
      }

      renderer.SetDrawColor(Color::WHITE);
      renderer.Clear();

      Rectangle dest = {(SCREEN_WIDTH - arrow_size.width) / 2,
                        (SCREEN_HEIGHT - arrow_size.height) / 2, arrow_size.width,
                        arrow_size.height};
      renderer.Copy(arrow, dest, angle, flip);

      renderer.Render();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
