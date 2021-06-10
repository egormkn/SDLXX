#include <sdlxx/core.h>

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 01: Hello World";
    const Dimensions window_size = {640, 480};

    CoreApi core_api(CoreApi::Flag::VIDEO);
    Window window(window_title, window_size);
    window.GetSurface().Fill(Color::WHITE);
    window.UpdateSurface();
    Timer::Delay(2000);
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
