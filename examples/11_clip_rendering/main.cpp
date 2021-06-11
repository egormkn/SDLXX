#include <array>

#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/image.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 11: Clip rendering";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);
    ImageApi image_api(ImageApi::Flag::PNG);

    Window window(window_title, window_size);

    Renderer renderer(window, Renderer::Flag::ACCELERATED);
    renderer.SetDrawColor(Color::WHITE);

    Texture dots;

    {
      Surface surface = ImageSurface("assets/dots.png");
      surface.SetColorKey(0x00FFFF);
      dots = Texture(renderer, surface);
    }

    std::array<Rectangle, 4> clips = {Rectangle(0, 0, 100, 100), Rectangle(100, 0, 100, 100),
                                      Rectangle(0, 100, 100, 100), Rectangle(100, 100, 100, 100)};

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

      renderer.Copy(dots, clips[0], {0, 0, 100, 100});
      renderer.Copy(dots, clips[1], {window_size.width - 100, 0, 100, 100});
      renderer.Copy(dots, clips[2], {0, window_size.height - 100, 100, 100});
      renderer.Copy(dots, clips[3], {window_size.width - 100, window_size.height - 100, 100, 100});

      renderer.RenderPresent();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
