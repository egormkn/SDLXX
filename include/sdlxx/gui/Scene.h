/**
 * @file Scene.h
 * @author Egor Makarenko
 * @brief Class that represents a 2D scene
 */

#pragma once

#ifndef SDLXX_GUI_SCENE_H
#define SDLXX_GUI_SCENE_H

#include <cstdint>

#include <sdlxx/core/events.h>
#include <sdlxx/core/renderer.h>
#include <sdlxx/core/window.h>
#include <sdlxx/gui/Object.h>

namespace sdlxx::gui {

class Scene : public Object {
public:
  enum class State { CREATED, STARTED, RESUMED, PAUSED, STOPPED, DESTROYED };

  virtual void update(uint32_t t, uint32_t dt) override;

  virtual void render(sdlxx::core::Renderer& renderer) override;

  virtual bool handleEvent(const sdlxx::core::Event& e) override;

  virtual State getState() const final;

protected:
  Scene() = default;

  virtual void onCreate();

  virtual void onStart();

  virtual void onResume();

  virtual void onPause();

  virtual void onStop();

  virtual void onDestroy();

  virtual void launch(std::shared_ptr<Scene> intent) final;

  virtual void finish() final;

  virtual bool hasIntent() const final;

  virtual bool isFinished() const final;

  virtual std::shared_ptr<sdlxx::core::Window> getWindow() const final;

private:
  bool finished = false;

  State state = State::DESTROYED;

  std::shared_ptr<Scene> intent;

  std::shared_ptr<sdlxx::core::Window> window;

  virtual void setWindow(std::shared_ptr<sdlxx::core::Window> window) final;

  Scene(const Scene&) = delete;

  Scene& operator=(const Scene&) = delete;

  friend class SceneManager;
};

}  // namespace sdlxx::gui

#endif  // SDLXX_GUI_SCENE_H
