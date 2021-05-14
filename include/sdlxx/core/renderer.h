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
 * @file Renderer.h
 * @author Egor Makarenko
 * @brief Class that describes a 2D rendering context
 */

#pragma once

#ifndef SDLXX_CORE_RENDERER_H
#define SDLXX_CORE_RENDERER_H

#include <tuple>
#include <unordered_set>
#include <vector>

#include <sdlxx/core/color.h>
#include <sdlxx/core/point.h>
#include <sdlxx/core/rectangle.h>
#include <sdlxx/core/texture.h>

class Box2DDrawer;

namespace sdlxx::core {

class Texture;

class Window;

class Surface;

/**
 * @brief Class that describes a 2D rendering context
 */
class Renderer {
public:
  enum class Option {
    /** The renderer is a software fallback */
    SOFTWARE = 0x00000001,
    /** The renderer uses hardware acceleration */
    ACCELERATED = 0x00000002,
    /** Present is synchronized with the refresh rate */
    PRESENTVSYNC = 0x00000004,
    /** The renderer supports rendering to texture */
    TARGETTEXTURE = 0x00000008
  };

  using OptionSet = std::unordered_set<Option>;

  /**
   * @brief The blend mode used in Renderer::copy() and drawing operations.
   */
  enum class BlendMode {
    /**
     * No blending
     * dstRGBA = srcRGBA
     */
    NONE = 0x00000000,
    /**
     * Alpha blending
     * dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
     * dstA = srcA + (dstA * (1-srcA))
     */
    BLEND = 0x00000001,
    /**
     * Additive blending
     * dstRGB = (srcRGB * srcA) + dstRGB
     * dstA = dstA
     */
    ADD = 0x00000002,
    /** Color modulate
     * dstRGB = srcRGB * dstRGB
     * dstA = dstA
     */
    MOD = 0x00000004,
    INVALID = 0x7FFFFFFF

    // Additional custom blend modes can be returned by composeCustomBlendMode()
  };

  /**
   * @brief Flip constants
   */
  enum class Flip {
    /** Do not flip */
    NONE = 0x00000000,
    /** Flip horizontally */
    HORIZONTAL = 0x00000001,
    /** Flip vertically */
    VERTICAL = 0x00000002
  };

  /**
   * @brief Create a 2D software rendering context for a surface.
   *
   * @param surface The surface where rendering is done.
   */
  Renderer(Surface& surface);

  /**
   * @brief Destroy the rendering context for a window and free associated
   * textures.
   */
  ~Renderer();

  // TODO: Some texture-related methods

  /**
   * @brief Set device independent resolution for rendering
   *
   * @param width  The width of the logical resolution
   * @param height The height of the logical resolution
   *
   * This function uses the viewport and scaling functionality to allow a fixed
   * logical resolution for rendering, regardless of the actual output
   * resolution. If the actual output resolution doesn't have the same aspect
   * ratio the output rendering will be centered within the output display.
   *
   * If the output display is a window, mouse events in the window will be
   * filtered and scaled so they seem to arrive within the logical resolution.
   *
   * @note If this function results in scaling or subpixel drawing by the
   *       rendering backend, it will be handled using the appropriate
   *       quality hints.
   */
  void setLogicalSize(int width, int height);

  /**
   * @brief Get device independent resolution for rendering
   *
   * @return Dimensions Size of a logical resolution
   */
  Dimensions getLogicalSize();

  /**
   * @brief Set whether to force integer scales for resolution-independent
   * rendering
   *
   * @param enable Enable or disable integer scaling
   *
   * This function restricts the logical viewport to integer values - that is,
   * when a resolution is between two multiples of a logical size, the viewport
   * size is rounded down to the lower multiple.
   */
  void setIntegerScale(bool enable);

  /**
   * @brief Get whether integer scales are forced for resolution-independent
   * rendering
   *
   * @return true if integer scales are forced for resolution-independent
   * rendering
   * @return false otherwise
   */
  bool getIntegerScale();

  /**
   * @brief Set the drawing area for rendering on the current target.
   *
   * The x,y of the viewport rect represents the origin for rendering.
   *
   * @param rectangle The rectangle representing the drawing area, or NULL to
   * set the viewport to the entire target.
   *
   * @note If the window associated with the renderer is resized, the viewport
   * is automatically reset.
   */
  void setViewport(const Rectangle& rectangle);

  /**
   * @brief Get the drawing area for the current target.
   *
   * @return Rectangle The rectangle that represents the drawing area.
   */
  Rectangle getViewport();

  /**
   * @brief Set the clip rectangle for the current target.
   *
   * @param rectangle A rectangle to set as the clip rectangle.
   */
  void setClipRectangle(const Rectangle& rectangle);

  /**
   * @brief Get the clip rectangle for the current target.
   *
   * @return Rectangle A current clip rectangle, or an empty rectangle if
   * clipping is disabled.
   */
  Rectangle getClipRectangle();

  /**
   * @brief Get whether clipping is enabled on the renderer.
   *
   * @return true if clipping is enabled
   * @return false otherwise
   */
  bool isClipEnabled();

  /**
   * @brief Set the drawing scale for rendering on the target.
   *
   * @param scaleX The horizontal scaling factor
   * @param scaleY The vertical scaling factor
   *
   * The drawing coordinates are scaled by the x/y scaling factors before they
   * are used by the renderer. This allows resolution independent drawing with a
   * single coordinate system.
   *
   * @note If this results in scaling or subpixel drawing by the rendering
   * backend, it will be handled using the appropriate quality hints. For best
   * results use integer scaling factors.
   */
  void setScale(float scaleX, float scaleY);

  /**
   * @brief Get the drawing scale for the current target.
   *
   * @return std::tuple<float, float> A tuple with the horizontal and vertical
   * scaling factors
   */
  std::tuple<float, float> getScale();

  /**
   * @brief Set the color used for drawing operations (Rect, Line and Clear)
   *
   * @param color The color used to draw on the rendering target.
   */
  void setColor(const Color& color);

  /**
   * @brief Get the color used for drawing operations (Rect, Line and Clear)
   *
   * @return Color The color used to draw on the rendering target.
   */
  Color getColor();

  /**
   * @brief Set the blend mode used for drawing operations (Fill and Line).
   *
   * @param blendMode
   *
   * @note If the blend mode is not supported, the closest supported mode is
   * chosen.
   */
  void setBlendMode(BlendMode blendMode);

  /**
   * @brief Get the blend mode used for drawing operations.
   *
   * @return BlendMode THe current blend mode.
   */
  BlendMode getBlendMode();

  /**
   * @brief Clear the current rendering target with the drawing color
   *
   * This function clears the entire rendering target, ignoring the viewport and
   * the clip rectangle.
   */
  void clear();

  /**
   * @brief Draw a point on the current rendering target.
   *
   * @param point The point to draw on the current target.
   */
  void drawPoint(const Point& point);

  /**
   * @brief Draw multiple points on the current rendering target.
   *
   * @param points The points to draw
   */
  void drawPoints(const std::vector<Point>& points);

  /**
   * @brief Draw a line on the current rendering target.
   *
   * @param start The start point
   * @param end The end point
   */
  void drawLine(const Point& start, const Point& end);

  /**
   * @brief Draw a series of connected lines on the current rendering target.
   *
   * @param points The points along the lines.
   */
  void drawLines(const std::vector<Point>& points);

  /**
   * @brief Draw a rectangle on the current rendering target.
   *
   * @param rectangle The rectangle to draw.
   */
  void drawRectangle(const Rectangle& rectangle);

  /**
   * @brief Draw some number of rectangles on the current rendering target.
   *
   * @param rectangles The rectangles to draw.
   */
  void drawRectangles(const std::vector<Rectangle>& rectangles);

  /**
   * @brief Fill a rectangle on the current rendering target with the drawing
   * color.
   *
   * @param rectangle The rectangle to fill.
   */
  void fillRectangle(const Rectangle& rectangle);

  /**
   * @brief Fill some number of rectangles on the current rendering target with
   * the drawing color.
   *
   * @param rectangles The rectangles to fill.
   */
  void fillRectangles(const std::vector<Rectangle>& rectangles);

  /**
   * @brief Copy a portion of the source texture to the current rendering
   * target, flipping it and rotating by angle around the given center
   *
   * @param texture The source texture.
   * @param source The source rectangle or std::nullopt for the entire texture.
   * @param destination The destination rectangle, or std::nullopt for the
   * entire rendering target
   * @param angle An angle in degrees that indicates the rotation that will be
   * applied to destination rectangle, rotating it in a clockwise direction
   * @param center A pointer to a point indicating the point around which
   * destination rectangle will be rotated (if std::nullopt, rotation will be
   * done around destination.width/2, destination.height/2).
   * @param flip Flip value stating which flipping actions should be performed
   * on the texture.
   */
  void copy(const Texture& texture,
            const std::optional<Rectangle>& source = std::nullopt,
            const std::optional<Rectangle>& destination = std::nullopt,
            double angle = 0.0,
            const std::optional<Point>& center = std::nullopt,
            Flip flip = Flip::NONE);

  /**
   * @brief Read pixels from the current rendering target.
   *
   * @param rectangle A rectangle to read, or std::nullopt for the entire render
   * target.
   * @param format The desired format of the pixel data, or 0 to use the format
   * of the rendering target
   * @param pitch The pitch of the pixels parameter.
   *
   * @return void* A pointer that is filled with the pixel data
   */
  void* readPixels(const std::optional<Rectangle>& rectangle,
                   uint32_t format = 0, int pitch = 0);

  /**
   * @brief Update the screen with rendering performed.
   */
  void render();

  // TODO: GL functions, Metal... something :)

  friend class Window;

  friend class Texture;

  friend class Box2DDrawer;

  void* renderer_ptr = nullptr;

private:
  Renderer(void* window_ptr, int driver,
           const std::unordered_set<Option>& options);

  Renderer(void* renderer_ptr);

  // Deleted copy constructor
  Renderer(const Renderer&) = delete;

  // Deleted copy assignment operator
  Renderer& operator=(const Renderer&) = delete;
};

Renderer::OptionSet operator|(const Renderer::Option& lhs,
                              const Renderer::Option& rhs);

Renderer::OptionSet operator|(Renderer::OptionSet&& lhs,
                              const Renderer::Option& rhs);

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_RENDERER_H
