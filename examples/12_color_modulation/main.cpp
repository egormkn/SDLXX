#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/image.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 12: Color modulation";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);
    ImageApi image_api(ImageApi::Flag::PNG);

    Window window(window_title, window_size);

    Renderer renderer(window, Renderer::Flag::ACCELERATED);
    renderer.SetDrawColor(Color::WHITE);

    Texture colors = ImageTexture(renderer, "assets/colors.png");

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

      renderer.RenderPresent();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
