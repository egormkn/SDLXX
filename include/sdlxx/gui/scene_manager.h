/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer (SDL2)

  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the SceneManager class that represents a manager of graphical scenes.
 */

#ifndef SDLXX_GUI_SCENE_MANAGER_H
#define SDLXX_GUI_SCENE_MANAGER_H

#include <stack>

#include <SDL_events.h>

#include "sdlxx/core/timer.h"
#include "sdlxx/gui/node.h"
#include "sdlxx/gui/scene.h"

namespace sdlxx {

/**
 * \brief A class that represents a stack-based manager of graphical scenes.
 */
class SceneManager {
public:
  /**
   * \brief Construct a SceneManager object with the given context.
   */
  explicit SceneManager(Node::Context context) : context(context) {}

  /**
   * \brief Push a new scene to the top of the stack.
   * \param scene A scene to add to the top of the stack.
   */
  void Push(std::unique_ptr<Scene> scene) {
    scenes.push_back(std::move(scene));
    scenes.back()->SetContext(&context);
  }

  /**
   * \brief Remove a scene from the top of the stack.
   * \return A scene that was removed from the top of the stack.
   */
  std::unique_ptr<Scene> Pop() {
    scenes.back()->SetContext(nullptr);
    std::unique_ptr<Scene> scene = std::move(scenes.back());
    scenes.pop_back();
    return scene;
  }

  /**
   * \brief Test whether the scene stack is empty.
   */
  bool Empty() { return scenes.empty(); }

  /**
   * \brief Run the event loop.
   */
  void Run() {
    uint32_t t = 0, dt = 10, accumulator = 0;
    uint32_t current_time = Timer::GetTicks();

    if (!scenes.empty()) {
      ActivateTop();
    }

    while (!scenes.empty()) {
      uint32_t new_time = Timer::GetTicks();
      uint32_t frame_time = std::min<uint32_t>(new_time - current_time, 250);
      current_time = new_time;

      Scene& current_scene = *scenes.back();

      if (!current_scene.IsActive() || current_scene.HasIntent()) {
        std::unique_ptr<Scene> intent = std::move(current_scene.intent);
        if (!current_scene.IsActive()) {
          Pop();
        } else {
          current_scene.Deactivate();
        }
        if (intent) {
          Push(std::move(intent));
        }
        if (!scenes.empty()) {
          ActivateTop();
        }
        continue;
      }

      HandleEvents(current_scene);

      if (scenes.empty() || !current_scene.IsActive()) {
        continue;
      }

      accumulator += frame_time;

      while (accumulator >= dt) {
        // previous = current;
        // integrate( current, t, dt );
        if (current_scene.IsActive()) {
          current_scene.Update(Time::Milliseconds(static_cast<int32_t>(dt)));
        }
        t += dt;
        accumulator -= dt;
        /*std::string str = "Game FPS: " + std::to_string((frameTime == 0 ? 0 :
        (int) (1000.0 / frameTime))); window->SetTitle(str);*/
      }

      Update(current_scene);

      Render(current_scene);
    }
  }

private:
  Node::Context context;
  std::vector<std::unique_ptr<Scene>> scenes;

  void ActivateTop() {
    Scene& scene = *scenes.back();
    scene.SetSize(context.window.GetSize());
    scene.Activate();
  }

  void HandleEvents(Scene& current_scene) {
    static Event event;

    while (Events::Poll(&event)) {
      if (event.type == SDL_QUIT) {
        bool handled = current_scene.HandleEvent(event);
        if (!handled) {
          current_scene.Deactivate();
          while (!scenes.empty()) {
            Pop();
          }
          break;
        }
      } else {
        current_scene.HandleEvent(event);
      }
    }
  }

  void Update(Scene& current_scene) {}

  void Render(Scene& current_scene) {
    context.renderer.SetDrawColor(Color::WHITE);
    context.renderer.Clear();
    context.renderer.Render(current_scene);
    context.renderer.RenderPresent();
  }
};
}  // namespace sdlxx

#endif  // SDLXX_GUI_SCENE_MANAGER_H
