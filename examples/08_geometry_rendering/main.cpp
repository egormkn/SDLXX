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
    CoreApi core_api(CoreApi::Flag::VIDEO);
    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    Window window("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, Window::Flag::SHOWN);

    Renderer renderer(window, Renderer::Flag::ACCELERATED);

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

      renderer.SetDrawColor(Color::RED);
      renderer.FillRectangle(
          {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

      renderer.SetDrawColor(Color::GREEN);
      renderer.DrawRectangle(
          {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3});

      renderer.SetDrawColor(Color::BLUE);
      renderer.DrawLine({0, SCREEN_HEIGHT / 2}, {SCREEN_WIDTH, SCREEN_HEIGHT / 2});

      renderer.SetDrawColor(Color::YELLOW);
      for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
        renderer.DrawPoint({SCREEN_WIDTH / 2, i});
      }

      renderer.Render();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
