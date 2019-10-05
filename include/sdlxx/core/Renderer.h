/**
 * @file Renderer.h
 * @author Egor Makarenko
 * @brief Class that describes a 2D rendering context
 */

#pragma once

#ifndef SDLXX_CORE_RENDERER_H
#define SDLXX_CORE_RENDERER_H

#include <unordered_set>

#include <sdlxx/core/Color.h>
#include <sdlxx/core/Rectangle.h>
#include <sdlxx/core/Texture.h>
#include <sdlxx/core/Window.h>

class Box2DDrawer;

namespace sdlxx::core {

class Texture;

/**
 * @brief Class that describes a 2D rendering context
 */
class Renderer {
public:
  enum class Option {
    SOFTWARE = 0x00000001,    /**< The renderer is a software fallback */
    ACCELERATED = 0x00000002, /**< The renderer uses hardware acceleration */
    PRESENTVSYNC =
        0x00000004, /**< Present is synchronized with the refresh rate */
    TARGETTEXTURE =
        0x00000008 /**< The renderer supports rendering to texture */
  };

  Renderer(Window& window, int driver,
                     const std::unordered_set<Option>& options);

  ~Renderer();

  void setLogicalSize(int width, int height);

  /**
   * @brief Set the color used for drawing operations
   *
   * @param color
   */
  void setColor(const Color& color);

  void render();

  void clear();

  // void renderCopy(const Texture& texture, const SDL_Rect* src = NULL,
  //                 const SDL_Rect* dest = NULL);

  void renderCopy(const Texture& texture, const Rectangle& source,
                  const Rectangle& destination);

  void renderCopy(const Texture& texture, const Rectangle& destination);

  void fillRect(const Rectangle& rectangle);

  friend std::shared_ptr<Renderer> Window::getRenderer();

  friend class Texture;

  friend class Box2DDrawer;

  void* renderer_ptr = nullptr;

private:
  Renderer(void* window_ptr, int driver, const std::unordered_set<Option>& options);

  Renderer(void* renderer_ptr);
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_RENDERER_H
