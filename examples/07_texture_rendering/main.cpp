#include <SDL_events.h>
#include <sdlxx/core/core_api.h>
#include <sdlxx/core/events.h>
#include <sdlxx/core/log.h>
#include <sdlxx/core/renderer.h>
#include <sdlxx/core/surface.h>
#include <sdlxx/core/window.h>
#include <sdlxx/image/image_api.h>
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

    Window window("SDL Tutorial", 640, 480, {Window::Flag::SHOWN});

    Renderer renderer(window, {Renderer::Flag::ACCELERATED});
    renderer.SetDrawColor(Color::WHITE);

    Texture image = ImageTexture(renderer, "texture.png");

    Event e;
    bool quit = false;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }

      renderer.Clear();
      renderer.Copy(image);
      renderer.Render();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
