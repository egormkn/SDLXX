/**
 * @file Image.h
 * @author Egor Makarenko
 * @brief Class that represents a surface loaded from an image
 */

#pragma once

#ifndef SDLXX_IMAGE_IMAGE_H
#define SDLXX_IMAGE_IMAGE_H

#include <string>

#include <sdlxx/core/Surface.h>

namespace sdlxx::image {

/**
 * @brief Class that represents a surface loaded from an image
 */
class Image : public sdlxx::core::Surface {
public:
  Image(const std::string& file);
};

}  // namespace sdlxx::image

#endif  // SDLXX_IMAGE_IMAGE_H
