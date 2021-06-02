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

    Texture dots;

    {
      Surface surface = ImageSurface("dots.png");
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
      renderer.Copy(dots, clips[1], {SCREEN_WIDTH - 100, 0, 100, 100});
      renderer.Copy(dots, clips[2], {0, SCREEN_HEIGHT - 100, 100, 100});
      renderer.Copy(dots, clips[3], {SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, 100, 100});

      renderer.Render();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
