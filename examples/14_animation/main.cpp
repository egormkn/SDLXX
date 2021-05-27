#include <SDL_events.h>
#include <SDL_render.h>
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
    CoreApi core_api({CoreApi::Flag::VIDEO});
    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    ImageApi image_api({ImageApi::Flag::PNG});

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    Window window("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, {Window::Flag::SHOWN});

    Renderer renderer(window, {Renderer::Flag::ACCELERATED, Renderer::Flag::PRESENTVSYNC});
    renderer.SetDrawColor(Color::WHITE);

    Texture stickman;
    Dimensions stickman_size;

    {
      Surface foo = ImageSurface("foo.png");
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
      Rectangle dst = {(SCREEN_WIDTH - src.width) / 2, (SCREEN_HEIGHT - src.height) / 2,
                       stickman_size.width / 4, stickman_size.height};
      renderer.Copy(stickman, src, dst);

      renderer.Render();

      frame = (frame + 1) % (clips.size() * 4);
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
