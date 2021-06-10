#include <SDL_events.h>
#include <sdlxx/core.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 08: Geometry rendering";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);

    Window window(window_title, window_size);

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
      renderer.FillRectangle({window_size.width / 4, window_size.height / 4, window_size.width / 2,
                              window_size.height / 2});

      renderer.SetDrawColor(Color::GREEN);
      renderer.DrawRectangle({window_size.width / 6, window_size.height / 6,
                              window_size.width * 2 / 3, window_size.height * 2 / 3});

      renderer.SetDrawColor(Color::BLUE);
      renderer.DrawLine({0, window_size.height / 2}, {window_size.width, window_size.height / 2});

      renderer.SetDrawColor(Color::YELLOW);
      for (int i = 0; i < window_size.height; i += 4) {
        renderer.DrawPoint({window_size.width / 2, i});
      }

      renderer.RenderPresent();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
