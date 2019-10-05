/**
 * @file Object.h
 * @author Egor Makarenko
 * @brief Class that represents a 2D object
 */

#pragma once

#ifndef SDLXX_CORE_OBJECT_H
#define SDLXX_CORE_OBJECT_H

#include <sdlxx/core/Events.h>
#include <sdlxx/core/Point.h>
#include <sdlxx/core/Renderer.h>

namespace sdlxx::core {

class Object {
protected:
  Object() = default;

public:
  virtual void update(Uint32 t, Uint32 dt, const Point& windowPoint) = 0;

  virtual void render(const std::shared_ptr<sdlxx::core::Renderer>& renderer) = 0;

  virtual bool handleEvent(const Event& e) = 0;

  virtual ~Object() = default;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_OBJECT_H
