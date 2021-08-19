/*!
  @file clipboard.hpp
  Include file for SDL clipboard handling
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
#ifndef SDLXX_CLIPBOARD_HPP
#define SDLXX_CLIPBOARD_HPP

#include "SDL_clipboard.h"

#include "detail/wrapper.hpp"
#include "macros.hpp"
#include "stdinc.hpp"

namespace sdl {

/*! @defgroup Clipboard Clipboard Handling

 This category contains functions for clipboard handling.

 @{
 */

//! Put UTF-8 text into the clipboard
//! @throws sdl::error on failure
inline void set_clipboard_text(const char* text) {
    SDLXX_CHECK(::SDL_SetClipboardText(text) == 0);
}

//! Put UTF-8 text into the clipboard
//! @throws sdl::error on failure
inline void set_clipboard_text(const string& text) {
    SDLXX_CHECK(detail::c_call(::SDL_SetClipboardText, text) == 0);
}

//! Get UTF-8 text from the clipboard
//! @returns The clipboard contents, or an empty string
inline string get_clipboard_text() {
    return detail::c_call(::SDL_GetClipboardText);
}

//! Returns a flag indicating whether the clipboard exists and contains a text
//! string that is non-empty
inline bool has_clipboard_text() {
    return detail::c_call(::SDL_HasClipboardText);
}

} // end namespace sdl

#endif // SDLXX_CLIPBOARD_HPP
