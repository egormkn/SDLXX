/**
 * @file Surface.h
 * @author Egor Makarenko
 * @brief Class that represents a collection of pixels used in software blitting
 */

#pragma once

#ifndef SDLXX_CORE_SURFACE_H
#define SDLXX_CORE_SURFACE_H

#include <sdlxx/core/Dimensions.h>
#include <sdlxx/core/Window.h>

// Forward declaration of Font class
namespace sdlxx::ttf {
class Font;
}  // namespace sdlxx::ttf

namespace sdlxx::core {

/**
 * @brief Class that represents a collection of pixels used in software blitting
 */
class Surface {
public:
  /**
   * @brief Destroy the surface
   */
  ~Surface();

  /**
   * @brief Get the size of the surface
   *
   * @return Dimensions The width and height of the surface
   */
  Dimensions getSize() const;

  static Surface fromBMP(const std::string& file);

  friend Surface Window::getSurface() const;

  friend class Texture;

  friend class sdlxx::ttf::Font;

private:
  void* surface_ptr = nullptr;

  Surface(void* surface_ptr);
};
}  // namespace sdlxx::core

#endif  // SDLXX_CORE_SURFACE_H
