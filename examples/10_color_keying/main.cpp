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

    Renderer renderer(window, {Renderer::Flag::ACCELERATED});
    renderer.SetDrawColor(Color::WHITE);

    Texture background = ImageTexture(renderer, "background.png");
    Texture stickman;
    Dimensions stickman_size;

    {
      Surface foo = ImageSurface("foo.png");
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

      renderer.Render();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
