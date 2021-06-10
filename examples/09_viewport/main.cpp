#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/image.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 09: Viewport";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);
    ImageApi image_api(ImageApi::Flag::PNG);

    Window window(window_title, window_size);

    Renderer renderer(window, Renderer::Flag::ACCELERATED);

    Texture image = ImageTexture(renderer, "assets/viewport.png");

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

      renderer.SetViewport({0, 0, window_size.width / 2, window_size.height / 2});
      renderer.Copy(image);

      renderer.SetViewport(
          {window_size.width / 2, 0, window_size.width / 2, window_size.height / 2});
      renderer.Copy(image);

      renderer.SetViewport({0, window_size.height / 2, window_size.width, window_size.height / 2});
      renderer.Copy(image);

      renderer.RenderPresent();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
