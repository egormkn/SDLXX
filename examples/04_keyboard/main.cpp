#include <vector>

#include <SDL_events.h>
#include <sdlxx/core/core_api.h>
#include <sdlxx/core/events.h>
#include <sdlxx/core/log.h>
#include <sdlxx/core/surface.h>
#include <sdlxx/core/window.h>

using namespace std;
using namespace sdlxx::core;

int main(int argc, char* args[]) {
  try {
    CoreApi subsystem({CoreApi::Flag::VIDEO});
    Window window("SDL Tutorial", 640, 480, {Window::Flag::SHOWN});
    Surface window_surface = window.GetSurface();

    vector<Surface> image_surfaces;
    for (const string& file : {"press.bmp", "up.bmp", "down.bmp", "left.bmp", "right.bmp"}) {
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
