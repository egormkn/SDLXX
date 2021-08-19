/*
  Simple DirectMedia Layer C++ Bindings
  Copyright (C) 2014 Tristan Brindle <t.c.brindle@gmail.com>

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

#ifndef SDLXX_STDINC_HPP
#define SDLXX_STDINC_HPP

#include "SDL.h"

/*
 Bring in std::experimental::optional
 */

#ifdef __cpp_lib_experimental_optional
#include <experimental/optional>
namespace sdl {
using std::experimental::optional;
using std::experimental::nullopt;
}
#else
#include "external/optional.hpp"
#endif

#include <sstream>
#include <string>

namespace sdl {
using std::string;

template <typename T>
void string_append(string& s, T&& entry) {
    std::ostringstream ss;
    ss << std::forward<T>(entry);
    s.append(ss.str());
}

inline void string_append(string& s, const string& entry) { s.append(entry); }

inline void string_append(string& s, const char* entry) { s.append(entry); }
}

/* Add namespaced typedefs for sized integer types. This is utterly pointless
   as the original versions are typedef'd in SDL_stdinc.h and so already exist
   in the root namespace, but still... */
namespace sdl {
using int8_t = Sint8;
using uint8_t = Uint8;
using int16_t = Sint16;
using uint16_t = Uint16;
using int32_t = Sint32;
using uint32_t = Uint32;
using int64_t = Sint64;
using uint64_t = Uint64;
using size_t = ::size_t;
}

#endif // SDLXX_STDINC_HPP
