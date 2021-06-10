#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/image.h>
#include <sdlxx/ttf.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 16: Fonts";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);
    ImageApi image_api(ImageApi::Flag::PNG);
    TtfApi ttf_api;

    Window window(window_title, window_size);

    Renderer renderer(window, Renderer::Flag::ACCELERATED | Renderer::Flag::PRESENTVSYNC);
    renderer.SetDrawColor(Color::WHITE);

    Font font("assets/xkcd-script.ttf", 28);

    Texture texture;
    Dimensions texture_size;

    {
      Surface text = font.RenderSolid("The quick brown fox jumps over the lazy dog", Color::BLACK);
      texture = Texture(renderer, text);
      texture_size = text.GetSize();
    }

    Event e;
    bool quit = false;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }

      renderer.SetDrawColor(Color::WHITE);
      renderer.Clear();

      Rectangle dest = {(window_size.width - texture_size.width) / 2,
                        (window_size.height - texture_size.height) / 2, texture_size.width,
                        texture_size.height};
      renderer.Copy(texture, dest);

      renderer.RenderPresent();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
