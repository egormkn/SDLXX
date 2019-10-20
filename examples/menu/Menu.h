#pragma once

#ifndef MENU_H
#define MENU_H

#include <string>

#include <sdlxx/core/Events.h>
#include <sdlxx/core/Renderer.h>
#include <sdlxx/gui/Scene.h>
#include <sdlxx/gui/Button.h>

class Menu : public sdlxx::gui::Scene {
public:
  Menu(const std::string& title);

  void onCreate() override;

  void onStart() override;

  void onResume() override;

  void onPause() override;

  void onStop() override;

  void onDestroy() override;

  bool handleEvent(const sdlxx::core::Event& e) override;

  void update(uint32_t t, uint32_t dt) override;

  void render(sdlxx::core::Renderer& renderer) override;

private:
  std::unique_ptr<sdlxx::gui::Button> runButton, exitButton;
  std::unique_ptr<sdlxx::core::Texture> background;
};

#endif  // MENU_H
