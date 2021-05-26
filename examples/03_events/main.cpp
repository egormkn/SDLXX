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
    Surface image_surface = Surface::LoadBMP("x.bmp");

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
