#include <vector>

#include <SDL_events.h>
#include <sdlxx/core.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 04: Keyboard";
    const Dimensions window_size = {640, 480};

    CoreApi core_api(CoreApi::Flag::VIDEO);
    Window window(window_title, window_size);
    Surface window_surface = window.GetSurface();

    vector<Surface> image_surfaces;
    for (const string& file : {"assets/press.bmp", "assets/up.bmp", "assets/down.bmp",
                               "assets/left.bmp", "assets/right.bmp"}) {
      image_surfaces.push_back(Surface::LoadBMP(file));
    }

    enum KeyPressSurfaces {
      KEY_PRESS_SURFACE_DEFAULT,
      KEY_PRESS_SURFACE_UP,
      KEY_PRESS_SURFACE_DOWN,
      KEY_PRESS_SURFACE_LEFT,
      KEY_PRESS_SURFACE_RIGHT
    };

    Surface* current = &image_surfaces.front();

    Event e;
    bool quit = false;

    while (!quit) {
      while (Events::Poll(&e)) {
        switch (e.type) {
          case SDL_QUIT:
            quit = true;
            break;
          case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
              case SDLK_UP:
                current = &image_surfaces[KEY_PRESS_SURFACE_UP];
                break;
              case SDLK_DOWN:
                current = &image_surfaces[KEY_PRESS_SURFACE_DOWN];
                break;
              case SDLK_LEFT:
                current = &image_surfaces[KEY_PRESS_SURFACE_LEFT];
                break;
              case SDLK_RIGHT:
                current = &image_surfaces[KEY_PRESS_SURFACE_RIGHT];
                break;
              default:
                current = &image_surfaces[KEY_PRESS_SURFACE_DEFAULT];
                break;
            }
            break;
        }
      }

      window_surface.Blit(*current);
      window.UpdateSurface();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
