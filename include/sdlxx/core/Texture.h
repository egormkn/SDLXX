/**
 * @file Texture.h
 * @author Egor Makarenko
 * @brief Class that represents a texture in an efficient driver-specific way
 */

#pragma once

#ifndef SDLXX_CORE_TEXTURE_H
#define SDLXX_CORE_TEXTURE_H

#include <memory>
#include <string>
#include <tuple>

#include <sdlxx/core/Renderer.h>

namespace sdlxx::core {

// Forward declaration of Renderer class
class Renderer;

// Forward declaration of Dimensions class
class Dimensions;

// Forward declaration of Color class
class Color;

// Forward declaration of Color class
class Surface;

/**
 * @brief Class that represents a texture in an efficient driver-specific way
 */
class Texture {
public:
  /**
   * @brief The access pattern allowed for a texture.
   */
  enum class Access {
    STATIC,    /**< Changes rarely, not lockable */
    STREAMING, /**< Changes frequently, lockable */
    TARGET     /**< Texture can be used as a render target */
  };

  using Format = uint32_t;

  /// Default pixel format
  static const Format UNKNOWN = 0;  // FIXME: Add all available formats

  /**
   * @brief Create a texture for a rendering context.
   *
   * @param renderer The renderer.
   * @param width The width of the texture in pixels.
   * @param height The height of the texture in pixels.
   * @param format The format of the texture.
   * @param access One of the enumerated values in Texture::Access.
   *
   * @throw if no rendering context is active, the format is unsupported, or
   * the width or height are out of range.
   *
   * @note The contents of the texture are not defined at creation.
   */
  Texture(std::shared_ptr<Renderer> renderer, int width, int height,
          Format format = UNKNOWN, Access access = Access::STATIC);

  /**
   * @brief Create a texture from an existing surface.
   *
   * @param renderer The renderer.
   * @param surface The surface containing pixel data used to fill the texture.
   *
   * @note The surface is not modified or freed by this function.
   */
  Texture(std::shared_ptr<Renderer> renderer, const Surface& surface);

  /**
   * @brief Destroy the texture.
   */
  ~Texture();

  /**
   * @brief Query the attributes of a texture.
   *
   * @return std::tuple<Dimensions, Format, Access> The attributes of a texture.
   */
  std::tuple<Dimensions, Format, Access> query() const;

  /**
   * @brief Query the dimensions of a texture.
   *
   * @return Dimensions The dimensions of a texture in pixels.
   */
  Dimensions getDimensions() const;

  /**
   * @brief Query the format of a texture.
   *
   * @return Format The raw format of the texture.
   *
   * @note The actual format may differ, but pixel transfers will use this
   * format.
   */
  Format getFormat() const;

  /**
   * @brief Query the actual access to the texture.
   *
   * @return Access The actual access to the texture.
   */
  Access getAccess() const;

  /**
   * @brief Set an additional color value used in render copy operations.
   *
   * @param color The color value multiplied into copy operations.
   */
  void setModulation(const Color& color);

  /**
   * @brief Get the additional color value used in render copy operations.
   *
   * @return Color The color value multiplied into copy operations.
   */
  Color getModulation() const;

  // TODO: setBlendMode/getBlendMode, update, lock/unlock

private:
  void* texture_ptr = nullptr;

  friend class Renderer;

  // Deleted copy constructor
  Texture(const Texture&) = delete;

  // Deleted copy assignment operator
  Texture& operator=(const Texture&) = delete;
};
}  // namespace sdlxx::core

#endif  // SDLXX_CORE_TEXTURE_H
