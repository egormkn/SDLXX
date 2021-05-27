#include <sdlxx/core/core_api.h>
#include <sdlxx/core/log.h>
#include <sdlxx/core/surface.h>
#include <sdlxx/core/timer.h>
#include <sdlxx/core/window.h>

using namespace std;
using namespace sdlxx::core;

int main(int argc, char* args[]) {
  try {
    CoreApi subsystem({CoreApi::Flag::VIDEO});
    Window window("SDL Tutorial", 640, 480, {Window::Flag::SHOWN});
    window.GetSurface().Fill(Color::WHITE);
    window.UpdateSurface();
    Timer::Delay(2000);
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
