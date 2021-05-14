/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer
  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgement in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * @file Surface.h
 * @author Egor Makarenko
 * @brief Class that represents a collection of pixels used in software blitting
 */

#pragma once

#ifndef SDLXX_CORE_SURFACE_H
#define SDLXX_CORE_SURFACE_H

#include <sdlxx/core/dimensions.h>
#include <sdlxx/core/window.h>

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
