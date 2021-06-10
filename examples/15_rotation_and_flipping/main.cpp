#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/image.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 15: Rotation and flippings";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);
    ImageApi image_api(ImageApi::Flag::PNG);

    Window window(window_title, window_size);

    Renderer renderer(window, Renderer::Flag::ACCELERATED | Renderer::Flag::PRESENTVSYNC);
    renderer.SetDrawColor(Color::WHITE);

    Texture arrow = ImageTexture(renderer, "assets/arrow.png");
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

      Rectangle dest = {(window_size.width - arrow_size.width) / 2,
                        (window_size.height - arrow_size.height) / 2, arrow_size.width,
                        arrow_size.height};
      renderer.Copy(arrow, dest, angle, flip);

      renderer.RenderPresent();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
