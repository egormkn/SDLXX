/*!
  @file macros.hpp
  Preprocessor macros used by sdl++

  @copyright (C) 2014 Tristan Brindle <t.c.brindle@gmail.com>

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

#ifndef SDLXX_MACROS_HPP
#define SDLXX_MACROS_HPP

#include "SDL_assert.h"

#include <stdexcept>

namespace sdl {

//! Exception type thrown by sdl++ functions if exceptions are enabled.
//! Inherits from std::runtime_error.
struct error : std::runtime_error {
    //! Constructor
    error(const char* what) : std::runtime_error(what) {}
};

} // end namespace sdl

/*! @macro SDLXX_CHECK
 The `SDLXX_CHECK` macro is used internally to wrap SDL calls which return an
 error code.

 By default, if an SDL call fails, the wrapper will throw an exception of
 type `sdl::error`, containing the error details as returned by
 `SDL_GetError()`.

 Alternatively, if `SDLXX_NO_EXCEPTIONS` is defined, then the
 exception will instead become a call to `SDL_assert()`. The assertion system
 in SDL is extremely powerful and flexible, and works somewhat like an exception
 system of its own. It can do very clever things such as automatically showing
 a dialog on an assertion failure, and allowing you to retry the failed
 condition.

 The final alternative for ultimate flexibility is to define the `SDLXX_CHECK`
 macro yourself. If you do this however you must ensure that the condition
 is checked _EXACTLY ONCE_, otherwise you will certainly encounter problems.
 */
#ifndef SDLXX_CHECK
#ifndef SDLXX_NO_EXCEPTIONS
#define SDLXX_CHECK(condition)                                                 \
    do {                                                                       \
        if (!(condition)) throw sdl::error(SDL_GetError());                    \
    } while (SDL_NULL_WHILE_LOOP_CONDITION);
#else
#define SDLXX_CHECK(condition) SDL_assert(condition)
#endif // SDLXX_NO_EXCEPTIONS
#endif // SDLXX_CHECK

/*! @macro SDLXX_ATTR_WARN_UNUSED_RESULT
 Expands to attribute `[[gnu::warn_unused_result]]` if the compiler is
 GCC-compatible (i.e. GCC or Clang), and nothing otherwise
 */
#ifdef __GNUC__
#define SDLXX_ATTR_WARN_UNUSED_RESULT [[gnu::warn_unused_result]]
#else
#define SDLXX_ATTR_WARN_UNUSED_RESULT
#endif

#endif // SDLXX_MACROS_HPP
