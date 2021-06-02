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
    CoreApi subsystem(CoreApi::Flag::VIDEO);
    Window window("SDL Tutorial", 640, 480, Window::Flag::SHOWN);
    Surface window_surface = window.GetSurface();

    Surface image_surface = Surface::LoadBMP("stretch.bmp");
    image_surface = image_surface.Convert(window_surface.GetFormat(), 0).value_or(image_surface);

    Event e;
    bool quit = false;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }

      window_surface.BlitScaled(image_surface);
      window.UpdateSurface();
    }
  } catch (std::exception& e) {
    Log::Error("[ERROR] " + std::string(e.what()));
  }
  return 0;
}
