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
 * \brief Header for the Renderer class that represents a 2D rendering context.
 */

#ifndef SDLXX_CORE_RENDERER_H
#define SDLXX_CORE_RENDERER_H

#include <cstdint>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "sdlxx/core/color.h"
#include "sdlxx/core/dimensions.h"
#include "sdlxx/core/exception.h"
#include "sdlxx/core/rectangle.h"
#include "sdlxx/utils/bitmask.h"

// Declaration of the underlying type
struct SDL_Renderer;

namespace sdlxx {

class Texture;
class Renderable;
class Surface;
class Window;
struct Point;

/**
 * \brief A class for Renderer-related exceptions.
 */
class RendererException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that represents a 2D rendering context.
 * \upstream SDL_Renderer
 */
class Renderer {
public:
  /**
   * \brief Flags used when creating a rendering context
   * \upstream SDL_RendererFlags
   */
  enum class Flag : uint32_t {
    SOFTWARE = 0x00000001,     /**< The renderer is a software fallback */
    ACCELERATED = 0x00000002,  /**< The renderer uses hardware acceleration */
    PRESENTVSYNC = 0x00000004, /**< Present is synchronized with the refresh rate */
    TARGETTEXTURE = 0x00000008 /**< The renderer supports rendering to texture */
  };

  /**
   * \brief A class that holds an information on the capabilities of a render driver or context.
   * \upstream SDL_RendererInfo
   */
  class Driver {
  public:
    /**
     * \brief Construct the driver info object
     * \param index The index of the driver to query information about.
     */
    explicit Driver(int index);

    /**
     * \brief Get the name of the renderer
     */
    std::string GetName() const;

    /**
     * \brief Get supported flags
     */
    BitMask<Flag> GetFlags() const;

    /**
     * \brief Get available texture formats
     */
    std::vector<uint32_t> GetTextureFormats() const;

    /**
     * \brief Get the maximum texture size
     */
    Dimensions GetMaximumTextureSize() const;

    /**
     * \brief Get the index of the driver
     */
    int GetIndex() const;

  private:
    int index;
  };

  /**
   * \brief Get the information about 2D rendering drivers available for the current display.
   *
   * A render driver is a set of code that handles rendering and texture
   * management on a particular display.  Normally there is only one, but
   * some drivers may have several available with different capabilities.
   *
   * \return std::vector<Driver> A vector of Renderer::Driver objects
   *
   * \sa Renderer()
   *
   * \upstream SDL_GetNumRenderDrivers
   * \upstream SDL_GetRenderDriverInfo
   */
  static std::vector<Driver> GetDrivers();

  /**
   * \brief Flip constants
   *
   * \sa Copy()
   *
   * \upstream SDL_RendererFlip
   */
  enum class Flip {
    NONE = 0x00000000,       /**< Do not flip */
    HORIZONTAL = 0x00000001, /**< Flip horizontally */
    VERTICAL = 0x00000002    /**< Flip vertically */
  };

  // TODO: SDL_CreateWindowAndRenderer

  /**
   * \brief Create a 2D rendering context for a window using the first driver that supports
   * specified flags.
   *
   * \param window The window where rendering is displayed.
   * \param flags  The flags for the rendering driver.
   *
   * \throw RendererException if there was an error.
   *
   * \upstream SDL_CreateRenderer
   */
  Renderer(Window& window, BitMask<Flag> flags);

  /**
   * \brief Create a 2D rendering context for a window.
   *
   * \param window The window where rendering is displayed.
   * \param driver The rendering driver to initialize.
   * \param flags  The flags for the rendering driver.
   *
   * \throw RendererException if there was an error.
   *
   * \upstream SDL_CreateRenderer
   */
  Renderer(Window& window, Driver driver, BitMask<Flag> flags);

  /**
   * \brief Create a 2D software rendering context for a surface.
   *
   * \param surface The surface where rendering is done.
   *
   * \throw RendererException if there was an error.
   *
   * \upstream SDL_CreateSoftwareRenderer
   */
  explicit Renderer(Surface& surface);

  /**
   * \brief Create an empty renderer
   */
  Renderer() = default;

  // TODO: SDL_GetRenderer, SDL_GetRendererInfo

  /**
   * \brief Get the output size in pixels of a rendering context.
   *
   * \upstream SDL_GetRendererOutputSize
   */
  Dimensions GetOutputSize() const;

  /**
   * \brief Determines whether the renderer supports the use of render targets
   *
   * \return true if supported, false if not.
   */
  bool RenderTargetSupported() const;

  /**
   * \brief Set a texture as the current rendering target.
   *
   * \param texture The targeted texture, which must be created with SDL_TEXTUREACCESS_TARGET flag
   *
   * \throw RendererException on error
   *
   * \upstream SDL_SetRenderTarget
   */
  void SetRenderTarget(Texture& texture);

  /**
   * \brief Reset the current rendering target to default target.
   *
   * \throw RendererException on error
   *
   * \upstream SDL_SetRenderTarget
   */
  void SetRenderTargetDefault();

  // TODO: SDL_GetRenderTarget

  /**
   * \brief Set device independent resolution for rendering
   *
   * \param renderer The renderer for which resolution should be set.
   * \param w      The width of the logical resolution
   * \param h      The height of the logical resolution
   *
   * This function uses the viewport and scaling functionality to allow a fixed logical
   * resolution for rendering, regardless of the actual output resolution.  If the actual
   * output resolution doesn't have the same aspect ratio the output rendering will be
   * centered within the output display.
   *
   * If the output display is a window, mouse events in the window will be filtered
   * and scaled so they seem to arrive within the logical resolution.
   *
   * \note If this function results in scaling or subpixel drawing by the
   *       rendering backend, it will be handled using the appropriate
   *       quality hints.
   *
   * \upstream SDL_RenderSetLogicalSize
   */
  void SetLogicalSize(Dimensions dimensions);

  /**
   * \brief Get device independent resolution for rendering
   *
   * \return Dimensions The width and height of a logical resolution
   *
   * \upstream SDL_RenderGetLogicalSize
   */
  Dimensions GetLogicalSize() const;

  /**
   * \brief Set whether to force integer scales for resolution-independent rendering
   *
   * \param is_enabled Enable or disable integer scaling
   *
   * This function restricts the logical viewport to integer values - that is,
   * when a resolution is between two multiples of a logical size, the viewport
   * size is rounded down to the lower multiple.
   *
   * \upstream SDL_RenderSetIntegerScale
   */
  void SetIntegerScale(bool is_enabled);

  /**
   * \brief Get whether integer scales are forced for resolution-independent rendering
   *
   * \return true if integer scales are forced for resolution-independent rendering
   * \return false otherwise
   *
   * \upstream SDL_RenderGetIntegerScale
   */
  bool GetIntegerScale() const;

  /**
   * \brief Set the drawing area for rendering on the current target.
   *
   * The x,y of the viewport rect represents the origin for rendering.
   *
   * \param rectangle The rectangle representing the drawing area.
   *
   * \throw RendererException on error.
   *
   * \note If the window associated with the renderer is resized,
   *       the viewport is automatically reset.
   *
   * \upstream SDL_RenderSetViewport
   */
  void SetViewport(const Rectangle& rectangle);

  /**
   * \brief Reset the drawing area for rendering to the entire target.
   *
   * \note If the window associated with the renderer is resized, the viewport
   * is automatically reset.
   *
   * \upstream SDL_RenderSetViewport
   */
  void ResetViewport();

  /**
   * \brief Get the drawing area for the current target.
   *
   * \return Rectangle The rectangle that represents the drawing area.
   *
   * \upstream SDL_RenderGetViewport
   */
  Rectangle GetViewport() const;

  /**
   * \brief Set the clip rectangle for the current target.
   *
   * \param rectangle A rectangle to set as the clip rectangle.
   *
   * \throw RendererException on error
   *
   * \upstream SDL_RenderSetClipRect
   */
  void SetClipRectangle(const Rectangle& rectangle);

  /**
   * \brief Disable clipping for the current target.
   *
   * \throw RendererException on error
   *
   * \upstream SDL_RenderSetClipRect
   */
  void ResetClipRectangle();

  /**
   * \brief Get the clip rectangle for the current target.
   *
   * \return Rectangle A current clip rectangle, or an empty rectangle if clipping is disabled.
   *
   * \upstream SDL_RenderGetClipRect
   */
  Rectangle GetClipRectangle() const;

  /**
   * \brief Get whether clipping is enabled on the renderer.
   *
   * \return true if clipping is enabled
   * \return false otherwise
   *
   * \upstream SDL_RenderIsClipEnabled
   */
  bool IsClipEnabled() const;

  /**
   * \brief Set the drawing scale for rendering on the target.
   *
   * \param scale_x The horizontal scaling factor
   * \param scale_y The vertical scaling factor
   *
   * The drawing coordinates are scaled by the x/y scaling factors before they
   * are used by the renderer. This allows resolution independent drawing with a
   * single coordinate system.
   *
   * \note If this results in scaling or subpixel drawing by the rendering
   * backend, it will be handled using the appropriate quality hints. For best
   * results use integer scaling factors.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderSetScale
   */
  void SetScale(float scale_x, float scale_y);

  /**
   * \brief Get the drawing scale for the current target.
   *
   * \return std::tuple<float, float> A tuple with the horizontal and vertical scaling factors
   *
   * \upstream SDL_RenderGetScale
   */
  std::tuple<float, float> GetScale() const;

  /**
   * \brief Set the color used for drawing operations (Rect, Line and Clear)
   *
   * \param color The color used to draw on the rendering target.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_SetRenderDrawColor
   */
  void SetDrawColor(Color color);

  /**
   * \brief Get the color used for drawing operations (Rect, Line and Clear)
   *
   * \throw RendererException on error.
   *
   * \return Color The color used to draw on the rendering target.
   *
   * \upstream SDL_GetRenderDrawColor
   */
  Color GetColor() const;

  // TODO: SDL_SetRenderDrawBlendMode, SDL_GetRenderDrawBlendMode

  /**
   * \brief Clear the current rendering target with the drawing color
   *
   * This function clears the entire rendering target, ignoring the viewport and the clip rectangle.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderClear
   */
  void Clear();

  /**
   * \brief Draw a point on the current rendering target.
   *
   * \param point The point to draw on the current target.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderDrawPoint
   */
  void DrawPoint(Point point);

  /**
   * \brief Draw multiple points on the current rendering target.
   *
   * \param points The points to draw
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderDrawPoints
   */
  void DrawPoints(const std::vector<Point>& points);

  /**
   * \brief Draw a line on the current rendering target.
   *
   * \param start The start point
   * \param end The end point
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderDrawLine
   */
  void DrawLine(Point line_start, Point line_end);

  /**
   * \brief Draw a series of connected lines on the current rendering target.
   *
   * \param points The points along the lines.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderDrawLines
   */
  void DrawLines(const std::vector<Point>& points);

  /**
   * \brief Draw a rectangle on the current rendering target.
   *
   * \param rectangle The rectangle to draw.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderDrawRect
   */
  void DrawRectangle(const Rectangle& rectangle);

  // TODO: SDL_RenderDrawRect for NULL rectangle

  /**
   * \brief Draw some number of rectangles on the current rendering target.
   *
   * \param rectangles The rectangles to draw.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderDrawRects
   */
  void DrawRectangles(const std::vector<Rectangle>& rectangles);

  /**
   * \brief Fill entire rendering target with the drawing color.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderFillRect
   */
  void Fill();

  /**
   * \brief Fill a rectangle on the current rendering target with the drawing color.
   *
   * \param rectangle The rectangle to fill.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderFillRect
   */
  void FillRectangle(const Rectangle& rectangle);

  /**
   * \brief Fill some number of rectangles on the current rendering target with the drawing color.
   *
   * \param rectangles The rectangles to fill.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderFillRects
   */
  void FillRectangles(const std::vector<Rectangle>& rectangles);

  /**
   * \brief Copy a texture to the current rendering target.
   *
   * \param texture The source texture.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderCopy
   */
  void Copy(const Texture& texture);

  /**
   * \brief Copy a texture to the current rendering target.
   *
   * \param texture The source texture.
   * \param dest    The destination rectangle.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderCopy
   */
  void Copy(const Texture& texture, const Rectangle& dest);

  /**
   * \brief Copy a portion of the texture to the current rendering target.
   *
   * \param texture The source texture.
   * \param source  The source rectangle.
   * \param dest    The destination rectangle.
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderCopy
   */
  void Copy(const Texture& texture, const Rectangle& source, const Rectangle& dest);

  /**
   * \brief Copy the source texture to the current rendering target, rotating it by angle around the
   *        center of the rendering target
   *
   * \param texture The source texture.
   * \param angle   An angle in degrees that indicates the rotation that will be applied to dest,
   *                rotating it in a clockwise direction
   * \param flip    A Flip value stating which flipping actions should be performed on the texture
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderCopyEx
   */
  void Copy(const Texture& texture, double angle, Flip flip = Flip::NONE);

  /**
   * \brief Copy the source texture to the current rendering target, rotating it by angle around the
   *        given center
   *
   * \param texture The source texture.
   * \param angle   An angle in degrees that indicates the rotation that will be applied to dest,
   *                rotating it in a clockwise direction
   * \param center  The point around which dest will be rotated.
   * \param flip    A Flip value stating which flipping actions should be performed on the texture
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderCopyEx
   */
  void Copy(const Texture& texture, double angle, Point center, Flip flip = Flip::NONE);

  /**
   * \brief Copy the source texture to the current rendering target, rotating it by
   * angle around the center of dest
   *
   * \param texture The source texture.
   * \param dest    The destination rectangle.
   * \param angle   An angle in degrees that indicates the rotation that will be applied to dest,
   *                rotating it in a clockwise direction
   * \param flip    A Flip value stating which flipping actions should be performed on the texture
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderCopyEx
   */
  void Copy(const Texture& texture, const Rectangle& dest, double angle, Flip flip = Flip::NONE);

  /**
   * \brief Copy a portion of the source texture to the current rendering target, rotating it by
   * angle around the center of dest
   *
   * \param texture The source texture.
   * \param source  The source rectangle.
   * \param dest    The destination rectangle.
   * \param angle   An angle in degrees that indicates the rotation that will be applied to dest,
   *                rotating it in a clockwise direction
   * \param flip    A Flip value stating which flipping actions should be performed on the texture
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderCopyEx
   */
  void Copy(const Texture& texture, const Rectangle& source, const Rectangle& dest, double angle,
            Flip flip = Flip::NONE);

  /**
   * \brief Copy a portion of the source texture to the current rendering target, rotating it by
   * angle around the given center
   *
   * \param texture The source texture.
   * \param dest    The destination rectangle.
   * \param angle   An angle in degrees that indicates the rotation that will be applied to dest,
   *                rotating it in a clockwise direction
   * \param center  The point around which dest will be rotated.
   * \param flip    A Flip value stating which flipping actions should be performed on the texture
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderCopyEx
   */
  void Copy(const Texture& texture, const Rectangle& dest, double angle, Point center,
            Flip flip = Flip::NONE);

  /**
   * \brief Copy a portion of the source texture to the current rendering target, rotating it by
   * angle around the given center
   *
   * \param texture The source texture.
   * \param source  The source rectangle.
   * \param dest    The destination rectangle.
   * \param angle   An angle in degrees that indicates the rotation that will be applied to dest,
   *                rotating it in a clockwise direction
   * \param center  The point around which dest will be rotated.
   * \param flip    A Flip value stating which flipping actions should be performed on the texture
   *
   * \throw RendererException on error.
   *
   * \upstream SDL_RenderCopyEx
   */
  void Copy(const Texture& texture, const Rectangle& source, const Rectangle& dest, double angle,
            Point center, Flip flip = Flip::NONE);

  // TODO: SDL_RenderDrawPointF, SDL_RenderDrawPointsF, SDL_RenderDrawLineF, SDL_RenderDrawLinesF,
  // SDL_RenderDrawRectF, SDL_RenderDrawRectsF, SDL_RenderFillRectF, SDL_RenderFillRectsF,
  // SDL_RenderCopyF, SDL_RenderCopyExF

  /**
   * \brief Read pixels from the current rendering target.
   *
   * \param format The desired format of the pixel data, or 0 to use the format
   *               of the rendering target
   * \param pixels A pointer to be filled in with the pixel data
   * \param pitch  The pitch of the pixels parameter.
   *
   * \throw RendererException if pixel reading is not supported.
   *
   * \warning This is a very slow operation, and should not be used frequently.
   *
   * \upstream SDL_RenderReadPixels
   */
  void ReadPixels(uint32_t format, void* pixels, int pitch);

  /**
   * \brief Read pixels from the current rendering target.
   *
   * \param rect   The rectangle to read.
   * \param format The desired format of the pixel data, or 0 to use the format
   *               of the rendering target
   * \param pixels A pointer to be filled in with the pixel data
   * \param pitch  The pitch of the pixels parameter.
   *
   * \throw RendererException if pixel reading is not supported.
   *
   * \warning This is a very slow operation, and should not be used frequently.
   *
   * \upstream SDL_RenderReadPixels
   */
  void ReadPixels(const Rectangle& rectangle, uint32_t format, void* pixels, int pitch);

  /**
   * \brief Update the screen with rendering performed.
   *
   * \upstream SDL_RenderPresent
   */
  void RenderPresent();

  // TODO: SDL_RenderFlush, SDL_RenderGetMetalLayer, SDL_RenderGetMetalCommandEncoder

  void Render(Renderable& renderable);

  /**
   * \brief Release the raw pointer to the underlying SDL_Renderer structure
   *
   * After this operation you are responsible for destroying the renderer
   *
   * \return The raw pointer to the underlying SDL_Renderer structure
   */
  SDL_Renderer* Release();

  friend class Texture;

private:
  struct Deleter {
    void operator()(SDL_Renderer* ptr) const;
  };

  std::unique_ptr<SDL_Renderer, Deleter> renderer_ptr;
};

}  // namespace sdlxx

ENABLE_BITMASK_OPERATORS(sdlxx::Renderer::Flag);

#endif  // SDLXX_CORE_RENDERER_H
