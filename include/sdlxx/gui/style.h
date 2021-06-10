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

#ifndef SDLXX_GUI_STYLE_H
#define SDLXX_GUI_STYLE_H

#include <optional>
#include <string>

#include <sdlxx/core/dimensions.h>

#include "sdlxx/core/color.h"

namespace sdlxx {

struct Style {
  enum class Visibility { VISIBLE, HIDDEN };

  enum class FontStyle { NORMAL, ITALIC };

  enum class FontWeight { NORMAL, BOLD };

  enum class Align { START, CENTER, END };

  std::optional<Dimensions> min_size;
  std::optional<Dimensions> max_size;
  std::optional<Dimensions> pref_size;
  std::optional<Visibility> visibility;
  std::optional<Color> text_color;
  std::optional<Color> background_color;
  std::optional<std::string> font_family;
  std::optional<uint32_t> font_size;
  std::optional<FontStyle> font_style;
  std::optional<Align> horizontal_align;
  std::optional<Align> vertical_align;

  void InheritFrom(const Style& other) {

  }

  void Set(Style&& other) {
    if (other.min_size) {
      std::swap(min_size, other.min_size);
    }
  }
};

}  // namespace sdlxx

#endif  // SDLXX_GUI_STYLE_H
