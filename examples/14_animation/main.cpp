#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/image.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 14: Animation";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);
    ImageApi image_api(ImageApi::Flag::PNG);

    Window window(window_title, window_size);

    Renderer renderer(window, Renderer::Flag::ACCELERATED | Renderer::Flag::PRESENTVSYNC);
    renderer.SetDrawColor(Color::WHITE);

    Texture stickman;
    Dimensions stickman_size;

    {
      Surface foo = ImageSurface("assets/foo.png");
      foo.SetColorKey(0x00FFFF);
      stickman = Texture(renderer, foo);
      stickman_size = foo.GetSize();
    }

    array<Rectangle, 4> clips = {Rectangle{0, 0, 64, 205}, Rectangle{64, 0, 64, 205},
                                 Rectangle{128, 0, 64, 205}, Rectangle{196, 0, 64, 205}};

    Event e;
    bool quit = false;

    int frame = 0;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }

      renderer.SetDrawColor(Color::WHITE);
      renderer.Clear();

      Rectangle& src = clips[frame / 4];
      Rectangle dst = {(window_size.width - src.width) / 2, (window_size.height - src.height) / 2,
                       stickman_size.width / 4, stickman_size.height};
      renderer.Copy(stickman, src, dst);

      renderer.RenderPresent();

      frame = (frame + 1) % (clips.size() * 4);
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
