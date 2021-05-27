/**
 * @file Object.h
 * @author Egor Makarenko
 * @brief Class that represents a 2D object
 */

#pragma once

#ifndef SDLXX_GUI_OBJECT_H
#define SDLXX_GUI_OBJECT_H

#include <cstdint>

#include <sdlxx/core/events.h>
#include <sdlxx/core/point.h>
#include <sdlxx/core/renderer.h>

namespace sdlxx::gui {

/**
 * @brief Class that represents a 2D object
 */
class Object {
public:
  virtual void update(uint32_t t, uint32_t dt) = 0;

  virtual void render(sdlxx::core::Renderer& renderer) = 0;

  virtual bool handleEvent(const sdlxx::core::Event& e) = 0;
};

}  // namespace sdlxx::gui

#endif  // SDLXX_GUI_OBJECT_H
