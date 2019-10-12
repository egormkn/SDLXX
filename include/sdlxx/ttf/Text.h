/**
 * @file Text.h
 * @author Egor Makarenko
 * @brief Class that represents a surface with rendered text
 */

#pragma once

#ifndef SDLXX_TTF_TEXT_H
#define SDLXX_TTF_TEXT_H

#include <string>
#include <sdlxx/core/Surface.h>

namespace sdlxx::ttf {

/**
 * @brief Class that represents a surface with rendered text
 */
class Text : public sdlxx::core::Surface {
public:
  enum class Mode { SOLID, SHADED, BLENDED };

  Text(const std::string& text);

  Text(void* surface_ptr);
};

}  // namespace sdlxx::ttf

#endif  // SDLXX_TTF_TEXT_H
