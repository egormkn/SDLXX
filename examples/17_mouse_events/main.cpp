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

    const int BUTTON_WIDTH = 300;
    const int BUTTON_HEIGHT = 200;
    const int TOTAL_BUTTONS = 4;

    std::array<Rectangle, Button::Sprite::TOTAL> clips;
    Texture texture = ImageTexture(renderer, "assets/button.png");
    std::array<Button, TOTAL_BUTTONS> buttons;

    for (int i = 0; i < clips.size(); ++i) {
      clips[i].x = 0;
      clips[i].y = i * 200;
      clips[i].width = BUTTON_WIDTH;
      clips[i].height = BUTTON_HEIGHT;
    }

    // Set buttons in corners
    buttons[0].SetPosition(0, 0);
    buttons[1].SetPosition(window_size.width - BUTTON_WIDTH, 0);
    buttons[2].SetPosition(0, window_size.height - BUTTON_HEIGHT);
    buttons[3].SetPosition(window_size.width - BUTTON_WIDTH, window_size.height - BUTTON_HEIGHT);

    Event e;
    bool quit = false;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }

        for (int i = 0; i < TOTAL_BUTTONS; ++i) {
          buttons.at(i).HandleEvent(e);
        }
      }

      renderer.SetDrawColor(Color::WHITE);
      renderer.Clear();

      for (int i = 0; i < TOTAL_BUTTONS; ++i) {
        // buttons[i].Render();
        Point position = buttons.at(i).GetPosition();
        renderer.Copy(texture, clips.at(buttons.at(i).GetSprite()),
                      {position.x, position.y, BUTTON_WIDTH, BUTTON_HEIGHT});
      }

      renderer.RenderPresent();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
