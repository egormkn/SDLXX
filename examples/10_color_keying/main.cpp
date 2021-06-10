#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/image.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 10: Color keying";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);
    ImageApi image_api(ImageApi::Flag::PNG);

    Window window(window_title, window_size);

    Renderer renderer(window, Renderer::Flag::ACCELERATED);
    renderer.SetDrawColor(Color::WHITE);

    Texture background = ImageTexture(renderer, "assets/background.png");
    Texture stickman;
    Dimensions stickman_size;

    {
      Surface foo = ImageSurface("assets/foo.png");
      foo.SetColorKey(0x00FFFF);
      stickman = Texture(renderer, foo);
      stickman_size = foo.GetSize();
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

      renderer.ResetViewport();
      renderer.Copy(background);

      renderer.Copy(stickman, {240, 190, stickman_size.width, stickman_size.height});

      renderer.RenderPresent();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
