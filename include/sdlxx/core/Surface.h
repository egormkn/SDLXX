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

namespace sdlxx::core {

// Forward declaration of Renderer class
class Renderer;

/**
 * @brief Class that represents a collection of pixels used in software blitting
 */
class Surface {
public:
  /**
   * @brief Destroy the surface
   */
  virtual ~Surface();

  /**
   * @brief Get the size of the surface
   *
   * @return Dimensions The width and height of the surface
   */
  virtual Dimensions getSize() const final;

  /**
   * @brief Load a surface from a BMP file
   *
   * @param file Path to the BMP file
   * @return Surface
   */
  static Surface fromBMP(const std::string& file);

  friend std::shared_ptr<Surface> Window::getSurface();

  friend class Texture;

  friend class Renderer;

protected:
  Surface(void* surface_ptr);

  void* surface_ptr = nullptr;

private:
  // Deleted copy constructor
  Surface(const Surface&) = delete;

  // Deleted copy assignment operator
  void operator=(const Surface&) = delete;
};
}  // namespace sdlxx::core

#endif  // SDLXX_CORE_SURFACE_H
