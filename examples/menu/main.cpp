#include <SDL_events.h>
#include <sdlxx/core.h>
#include <sdlxx/gui.h>
#include <sdlxx/image.h>
#include <sdlxx/ttf.h>

using namespace std;
using namespace sdlxx;

class Menu : public Scene {
public:
  explicit Menu(int index) : Scene("Menu" + to_string(index)), index(index) {
    auto layout = std::make_unique<ManualLayout>();
    layout->AddChild(
        std::make_unique<Button>(
            "Run the game", [this, index] { this->SetIntent(std::make_unique<Menu>(index + 1)); }),
        {30, 30, 200, 70});
    layout->AddChild(std::make_unique<Button>("Exit", [this] { this->Finish(); }),
                     {30, 110, 200, 70});
    AddChild(std::move(layout));
  }

  void Render(Renderer& renderer) const override {
    renderer.Copy(*background);
    renderer.Copy(*text, {{200, 200}, text_size});
    ParentNode::Render(renderer);
  }

protected:
  void OnActivate() override {
    Scene::OnActivate();
    Font font("assets/xkcd-script.ttf", 100);
    Surface text_surface = font.RenderBlended(std::to_string(index), Color::YELLOW);
    text_size = text_surface.GetSize();
    text = std::make_unique<Texture>(GetContext()->renderer, text_surface);
    background = std::make_unique<ImageTexture>(GetContext()->renderer, "assets/menu.png");
  }
  void OnDeactivate() override {
    background = nullptr;
    text = nullptr;
    Scene::OnDeactivate();
  }

private:
  int index;
  std::unique_ptr<Texture> background;
  std::unique_ptr<Texture> text;
  Dimensions text_size;
};

int main(int argc, char* args[]) {
  try {
    const string window_title = "Game menu";
    const Dimensions window_size = {640, 480};

    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    CoreApi core_api(CoreApi::Flag::VIDEO | CoreApi::Flag::EVENTS);
    ImageApi image_api(ImageApi::Flag::PNG);
    TtfApi ttf_api;

    using WFlag = Window::Flag;
    Window window(window_title, window_size,
                  WFlag::SHOWN | WFlag::RESIZABLE | WFlag::ALLOW_HIGHDPI);

    using RFlag = Renderer::Flag;
    Renderer renderer(window, RFlag::ACCELERATED | RFlag::PRESENTVSYNC);
    // renderer.SetLogicalSize(window_size);
    renderer.SetDrawColor(Color::WHITE);

    SceneManager manager({window, renderer});

    manager.Push(std::make_unique<Menu>(1));
    manager.Run();
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
