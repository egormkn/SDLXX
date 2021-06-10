#include <SDL_events.h>
#include <sdlxx/core.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 03: Events";
    const Dimensions window_size = {640, 480};

    CoreApi core_api(CoreApi::Flag::VIDEO);
    Window window(window_title, window_size);
    Surface window_surface = window.GetSurface();
    Surface image_surface = Surface::LoadBMP("assets/x.bmp");

    Event e;
    bool quit = false;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }

      window_surface.Blit(image_surface);
      window.UpdateSurface();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
