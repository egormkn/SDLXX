#include <array>

#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/image.h>

#include "./button.h"

using namespace std;
using namespace sdlxx;

int main(int argc, char* args[]) {
  try {
    const string window_title = "Example 17: Mouse events";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO);
    ImageApi image_api(ImageApi::Flag::PNG);

    Window window(window_title, window_size);

    Renderer renderer(window, Renderer::Flag::ACCELERATED | Renderer::Flag::PRESENTVSYNC);
    renderer.SetDrawColor(Color::WHITE);

    const Dimensions button_size = {window_size.width / 2, window_size.height / 2};

    std::array<Rectangle, Button::Sprite::TOTAL> clips;
    for (int i = 0; i < clips.size(); ++i) {
      clips.at(i).x = 0;
      clips.at(i).y = i * 200;
      clips.at(i).width = 300;
      clips.at(i).height = 200;
    }

    Button::SetTexture(ImageTexture(renderer, "assets/button.png"), clips);

    std::array<Button, 4> buttons;

    for (Button& button : buttons) {
      button.SetSize({window_size.width / 2, window_size.height / 2});
    }

    // Set buttons in corners
    buttons[0].SetPosition(0, 0);
    buttons[1].SetPosition(window_size.width - button_size.width, 0);
    buttons[2].SetPosition(0, window_size.height - button_size.height);
    buttons[3].SetPosition(window_size.width - button_size.width,
                           window_size.height - button_size.height);

    Event e;
    bool quit = false;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }

        for (Button& button : buttons) {
          button.HandleEvent(e);
        }
      }

      renderer.SetDrawColor(Color::WHITE);
      renderer.Clear();

      for (Button& button : buttons) {
        renderer.Render(button);
      }

      renderer.RenderPresent();
    }

    // Clear static texture, so it is destroyed properly before SDL shutdown
    Button::SetTexture({}, {});
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
