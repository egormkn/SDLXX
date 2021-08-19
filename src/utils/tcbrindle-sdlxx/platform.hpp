/*
  @file platform.hpp
  Information about the current platform

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

#ifndef SDLXX_PLATFORM_HPP
#define SDLXX_PLATFORM_HPP

#include "SDL_platform.h"

namespace sdl {

/*!
 @defgroup Platform Platform Detection
 This category contains functions for handling information about the current
 platform.

 @{
 */

/*!
 Gets the name of the platform. If the correct platform name is not
 available, returns a string beginning with the text "Unknown".
 */
inline const char* get_platform_name() { return ::SDL_GetPlatform(); }

} // end namespace sdl

#endif // SDLXX_PLATFORM_HPP
