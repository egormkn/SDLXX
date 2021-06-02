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
 * \file
 * \brief Header for the Surface class that represents a collection of pixels.
 */

#ifndef SDLXX_CORE_SURFACE_H
#define SDLXX_CORE_SURFACE_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "sdlxx/core/color.h"
#include "sdlxx/core/dimensions.h"
#include "sdlxx/core/exception.h"
#include "sdlxx/core/rectangle.h"

// Declaration of the underlying type
struct SDL_Surface;

// Declaration of used types
struct SDL_PixelFormat;

namespace sdlxx::core {

/**
 * \brief A class for Surface-related exceptions.
 */
class SurfaceException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that represents a collection of pixels used in software blitting.
 *
 * \note  This class should be treated as read-only, except for \c GetPixels(),
 *        which, if not equal to \a nullptr, contains the raw pixel data for the surface.
 *
 * \upstream SDL_Surface
 */
class Surface {
public:
  /**
   * \brief Allocate an RGB surface.
   *
   * If the depth is 4 or 8 bits, an empty palette is allocated for the surface.
   * If the depth is greater than 8 bits, the pixel format is set using the flags '[RGB]mask'.
   *
   * If the function runs out of memory, it will throw an exception.
   *
   * \param width The width in pixels of the surface to create.
   * \param height The height in pixels of the surface to create.
   * \param depth The depth in bits of the surface to create.
   * \param Rmask The red mask of the surface to create.
   * \param Gmask The green mask of the surface to create.
   * \param Bmask The blue mask of the surface to create.
   * \param Amask The alpha mask of the surface to create.
   *
   * \upstream SDL_CreateRGBSurface
   */
  Surface(int width, int height, int depth, uint32_t Rmask, uint32_t Gmask, uint32_t Bmask,
          uint32_t Amask);

  /**
   * \brief Allocate an RGB surface using pixel format.
   *
   * \param width The width in pixels of the surface to create.
   * \param height The height in pixels of the surface to create.
   * \param depth The depth in bits of the surface to create.
   * \param format The pixel format of the surface to create.
   *
   * \upstream SDL_CreateRGBSurfaceWithFormat
   */
  Surface(int width, int height, int depth, uint32_t format);

  /**
   * \brief Create a surface from raw pixel data.
   *
   * \param pixels The pointer to the pixels data of the surface to create.
   * \param width The width in pixels of the surface to create.
   * \param height The height in pixels of the surface to create.
   * \param depth The depth in bits of the surface to create.
   * \param pitch
   * \param Rmask The red mask of the surface to create.
   * \param Gmask The green mask of the surface to create.
   * \param Bmask The blue mask of the surface to create.
   * \param Amask The alpha mask of the surface to create.
   *
   * \upstream SDL_CreateRGBSurfaceFrom
   */
  Surface(void* pixels, int width, int height, int depth, int pitch, uint32_t Rmask, uint32_t Gmask,
          uint32_t Bmask, uint32_t Amask);

  /**
   * \brief Create a surface from raw pixel data using pixel format.
   *
   * \param pixels The pointer to the pixels data of the surface to create.
   * \param width The width in pixels of the surface to create.
   * \param height The height in pixels of the surface to create.
   * \param depth The depth in bits of the surface to create.
   * \param pitch
   * \param format The pixel format of the surface to create.
   *
   * \upstream SDL_CreateRGBSurfaceWithFormatFrom
   */
  Surface(void* pixels, int width, int height, int depth, int pitch, uint32_t format);

  /**
   * \brief Create an empty surface
   */
  Surface() = default;

  /**
   * \brief Create a surface from the raw pointer to SDL_Surface
   *
   * \param ptr The raw pointer to SDL_Surface
   */
  explicit Surface(SDL_Surface* ptr);

  /**
   * \brief Copy constructor
   *
   * Creates a new surface identical to the existing surface
   *
   * \upstream SDL_DuplicateSurface
   */
  Surface(const Surface& other);

  /**
   * \brief Copy assignment operator
   *
   * Creates a new surface identical to the existing surface
   *
   * \upstream SDL_DuplicateSurface
   */
  Surface& operator=(const Surface& other);

  /**
   * \brief Move constructor
   */
  Surface(Surface&& other) = default;

  /**
   * \brief Move assignment operator
   */
  Surface& operator=(Surface&& other) = default;

  /**
   * \brief Destroy the surface
   */
  virtual ~Surface() = default;

  // TODO: SDL_SetSurfacePalette

  /**
   * \brief Set up a surface for directly accessing the pixels.
   *
   * Between calls to Lock() / Unlock(), you can write to and read from \c GetPixels(),
   * using the pixel format stored in \c GetPixelFormat(). Once you are done accessing the surface,
   * you should use Unlock() to release it.
   *
   * Not all surfaces require locking. If the surface can be accessed at any time and the
   * pixel format of the surface will not change, this method does nothing.
   *
   * No operating system or library calls should be made between lock/unlock
   * pairs, as critical system locks may be held during this time.
   *
   * \return true if the lock was acquired, false if the surface couldn't be locked.
   *
   * \sa Unlock()
   *
   * \upstream SDL_LockSurface
   */
  bool Lock();

  /**
   * \brief Unlock a surface locked by Lock().
   *
   * \sa Lock()
   *
   * \upstream SDL_UnlockSurface
   */
  void Unlock();

  /**
   * \brief Load a surface from a BMP file
   *
   * \param file Path to the BMP file
   *
   * \throw SurfaceException if there was an error.
   *
   * \upstream SDL_LoadBMP
   */
  static Surface LoadBMP(const std::string& file);

  /**
   * \brief Save a surface to the BMP file.
   *
   * \param file Path to the new BMP file.
   *
   * \throw SurfaceException if there was an error.
   *
   * \upstream SDL_SaveBMP
   */
  void SaveBMP(const std::string& file) const;

  // TODO: SDL_LoadBMP_RW, SDL_SaveBMP_RW, SDL_SetSurfaceRLE, SDL_HasSurfaceRLE

  /**
   * \brief Sets the color key (transparent pixel) in a blittable surface.
   *
   * \param color The transparent pixel color.
   *
   * \throw SurfaceException if the surface is not valid
   *
   * \upstream SDL_SetColorKey
   */
  void SetColorKey(Color color);

  /**
   * \brief Sets the color key (transparent pixel) in a blittable surface.
   *
   * \throw SurfaceException if the surface is not valid
   *
   * \upstream SDL_SetColorKey
   */
  void ResetColorKey();

  /**
   * \brief Returns whether the surface has a color key
   *
   * \return true if the surface has a color key, or false if the surface has no color key
   *
   * \upstream SDL_HasColorKey
   */
  bool HasColorKey() const;

  // TODO: SDL_GetColorKey, SDL_SetSurfaceColorMod, SDL_GetSurfaceColorMod,
  // SDL_SetSurfaceAlphaMod, SDL_GetSurfaceAlphaMod, SDL_SetSurfaceBlendMode,
  // SDL_GetSurfaceBlendMode

  /**
   * \brief Set the clipping rectangle for the destination surface in a blit.
   *
   * \return false If the clip rectangle doesn't intersect the surface. In this case blits will be
   *               completely clipped.
   * \return true Otherwise, blits to the surface will be clipped to the intersection of the surface
   *              area and the clipping rectangle.
   *
   * \note Blits are automatically clipped to the edges of the source
   * and destination surfaces.
   *
   * \upstream SDL_SetClipRect
   */
  bool SetClipRectangle(const Rectangle& rectangle);

  /**
   * \brief Disable the clipping rectangle for the destination surface in a blit.
   *
   * \upstream SDL_SetClipRect
   */
  void DisableClipRectangle();

  /**
   * \brief Get the clipping rectangle for the destination surface in a blit.
   *
   * \upstream SDL_GetClipRect
   */
  Rectangle GetClipRectangle() const;

  /**
   * \brief Create a new surface of the specified format, and then copy and map
   * the given surface to it so the blit of the converted surface will be as
   * fast as possible. If this function fails, it returns NULL.
   *
   * The \c flags parameter is passed to SDL_CreateRGBSurface() and has those
   * semantics.  You can also pass ::SDL_RLEACCEL in the flags parameter and
   * SDL will try to RLE accelerate colorkey and alpha blits in the resulting
   * surface.
   *
   * \upstream SDL_ConvertSurface
   * \upstream SDL_ConvertSurfaceFormat
   */
  std::optional<Surface> Convert(const SDL_PixelFormat* fmt, uint32_t flags);
  std::optional<Surface> ConvertFormat(uint32_t pixel_format, uint32_t flags);

  /**
   * \brief Copy a block of pixels of one format to another format.
   *
   * \throw SurfaceException if there was an error.
   *
   * \upstream SDL_ConvertPixels
   */
  static void ConvertPixels(int width, int height, uint32_t src_format, const void* src,
                            int src_pitch, uint32_t dst_format, void* dst, int dst_pitch);

  /**
   * \brief Performs a fast fill of the surface with \c color.
   *
   * \throw SurfaceException on error.
   *
   * \upstream SDL_FillRect
   */
  void Fill(const Color& color);

  /**
   * \brief Performs a fast fill of the given rectangle with \c color.
   *
   * \throw SurfaceException on error.
   *
   * \upstream SDL_FillRect
   */
  void FillRectangle(const Rectangle& rectangle, const Color& color);

  /**
   * \brief Performs a fast fill of the given rectangles with \c color.
   *
   * \throw SurfaceException on error.
   *
   * \upstream SDL_FillRects
   */
  void FillRectangles(const std::vector<Rectangle>& rectangles, const Color& color);

  /**
   * \brief Performs a fast blit to the current surface.
   *
   * This assumes that the source and destination rectangles are
   * the same size.  If either \c srcrect or \c dstrect are NULL, the entire
   * surface (\c src or \c dst) is copied.  The final blit rectangles are saved
   * in \c srcrect and \c dstrect after all clipping is performed.
   *
   * \throw SurfaceException if the blit is unsuccessful.
   *
   * The blit function should not be called on a locked surface.
   *
   * The blit semantics for surfaces with and without blending and colorkey
   * are defined as follows:
   * \verbatim
     RGBA->RGB:
       Source surface blend mode set to SDL_BLENDMODE_BLEND:
         alpha-blend (using the source alpha-channel and per-surface alpha)
         SDL_SRCCOLORKEY ignored.
       Source surface blend mode set to SDL_BLENDMODE_NONE:
         copy RGB.
         if SDL_SRCCOLORKEY set, only copy the pixels matching the
         RGB values of the source color key, ignoring alpha in the
         comparison.

     RGB->RGBA:
       Source surface blend mode set to SDL_BLENDMODE_BLEND:
         alpha-blend (using the source per-surface alpha)
       Source surface blend mode set to SDL_BLENDMODE_NONE:
         copy RGB, set destination alpha to source per-surface alpha value.
       both:
         if SDL_SRCCOLORKEY set, only copy the pixels matching the
         source color key.

     RGBA->RGBA:
       Source surface blend mode set to SDL_BLENDMODE_BLEND:
         alpha-blend (using the source alpha-channel and per-surface alpha)
         SDL_SRCCOLORKEY ignored.
       Source surface blend mode set to SDL_BLENDMODE_NONE:
         copy all of RGBA to the destination.
         if SDL_SRCCOLORKEY set, only copy the pixels matching the
         RGB values of the source color key, ignoring alpha in the
         comparison.

     RGB->RGB:
       Source surface blend mode set to SDL_BLENDMODE_BLEND:
         alpha-blend (using the source per-surface alpha)
       Source surface blend mode set to SDL_BLENDMODE_NONE:
         copy RGB.
       both:
         if SDL_SRCCOLORKEY set, only copy the pixels matching the
         source color key.
     \endverbatim
   *
   * You should call Blit() unless you know exactly how SDL blitting works internally
   * and how to use the other blit functions.
   *
   * \upstream SDL_BlitSurface
   */
  void Blit(const Surface& source);
  void Blit(const Surface& source, const Rectangle& source_rect, const Rectangle& dest_rect);

  // TODO: SDL_LowerBlit, SDL_SoftStretch

  /**
   * This is the public scaled blit function, and it performs
   * rectangle validation and clipping.
   *
   * \upstream SDL_BlitScaled
   */
  void BlitScaled(const Surface& source);
  void BlitScaled(const Surface& source, const Rectangle& source_rect, const Rectangle& dest_rect);

  // TODO: SDL_LowerBlitScaled, SDL_SetYUVConversionMode, SDL_GetYUVConversionMode,
  // SDL_GetYUVConversionModeForResolution

  /**
   * \brief Get the size of the surface.
   *
   * \return Dimensions The width and height of the surface.
   *
   * \upstream SDL_Surface::x
   * \upstream SDL_Surface::y
   */
  Dimensions GetSize() const;

  /**
   * \brief Get the pointer to the surface pixel data.
   *
   * \return void* The pointer to the surface pixel data.
   *
   * \upstream SDL_Surface::pixels
   */
  void* GetPixels() const;

  /**
   * \brief Get the pointer to the surface pixel format.
   *
   * \return SDL_PixelFormat* The pointer to the surface pixel format.
   *
   * \upstream SDL_Surface::format
   */
  SDL_PixelFormat* GetFormat() const;

  /**
   * \brief Get the raw pointer to SDL_Surface.
   *
   * After this operation you are responsible for freeing the memory of the surface.
   *
   * \return A pointer to the SDL_Surface
   */
  SDL_Surface* Release();

  // Friend declarations
  friend class Renderer;
  friend class Window;
  friend class Texture;

protected:
  struct Deleter {
    void operator()(SDL_Surface* ptr) const;
  };

  std::unique_ptr<SDL_Surface, Deleter> surface_ptr;
};

/**
 * \brief Helper class for RAII-style surface lock.
 *
 * \upstream SDL_LockSurface
 * \upstream SDL_UnlockSurface
 */
class SurfaceLock {
public:
  explicit SurfaceLock(Surface& surface);

  ~SurfaceLock();

  // Deleted copy constructor
  SurfaceLock(const SurfaceLock&) = delete;

  // Deleted copy assignment operator
  SurfaceLock& operator=(const SurfaceLock&) = delete;

private:
  Surface& surface;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_SURFACE_H
