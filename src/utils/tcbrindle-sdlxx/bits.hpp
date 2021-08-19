/*
  @file bits.hpp
  Functions for fiddling with bits and bitmasks.

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
#ifndef SDLXX_BITS_HPP
#define SDLXX_BITS_HPP

#include "SDL_bits.h"

#include "stdinc.hpp"

namespace sdl {

/*!
 @defgroup Bits Bit-level Operations

 This category contains functions for bit-level operations ("bit-twiddling").

 @{
 */

/*!
 Get the index of the most significant bit. Result is undefined when called
 with 0. This operation can also be stated as "count leading zeroes" and
 "log base 2".

 @return Index of the most significant bit, or -1 if the value is 0.
 */
inline int most_significant_bit_index(uint32_t x) noexcept {
    return ::SDL_MostSignificantBitIndex32(x);
}

} // end namespace sdl

#endif // SDLXX_BITS_HPP
