#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/image.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 13: Alpha blending";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);
    ImageApi image_api(ImageApi::Flag::PNG);

    Window window(window_title, window_size);

    Renderer renderer(window, Renderer::Flag::ACCELERATED);
    renderer.SetDrawColor(Color::WHITE);

    Texture fadein = ImageTexture(renderer, "assets/fadein.png");
    Texture fadeout = ImageTexture(renderer, "assets/fadeout.png");
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

      renderer.RenderPresent();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
