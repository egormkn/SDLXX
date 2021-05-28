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
#include <sdlxx/ttf/font.h>
#include <sdlxx/ttf/ttf_api.h>

using namespace std;
using namespace sdlxx::core;
using namespace sdlxx::image;
using namespace sdlxx::ttf;

int main(int argc, char* args[]) {
  try {
    CoreApi core_api({CoreApi::Flag::VIDEO});
    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    ImageApi image_api({ImageApi::Flag::PNG});

    TtfApi ttf_api;

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    Window window("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, {Window::Flag::SHOWN});

    Renderer renderer(window, {Renderer::Flag::ACCELERATED, Renderer::Flag::PRESENTVSYNC});
    renderer.SetDrawColor(Color::WHITE);

    Font font("xkcd-script.ttf", 28);

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

      Rectangle dest = {(SCREEN_WIDTH - texture_size.width) / 2,
                        (SCREEN_HEIGHT - texture_size.height) / 2, texture_size.width,
                        texture_size.height};
      renderer.Copy(texture, dest);

      renderer.Render();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
