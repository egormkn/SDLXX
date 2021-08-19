/*
  @file endian.hpp
  Functions for reading and writing endian-specific values
  @copyright (C) 2014-2016 Tristan Brindle <t.c.brindle@gmail.com>

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
#ifndef SDLXX_ENDIAN_HPP
#define SDLXX_ENDIAN_HPP

#include "SDL_endian.h"

#include <type_traits>
#include <utility>

namespace sdl {

/*! @defgroup Endian Byte Order and Byte Swapping

  This category contains functions for handling endian-specific values.

  Endianness comes in two forms - big and little.

    - `byte_order::little_endian` means byte order is 1234, where the smaller
       (little) numbered position comes first
    - `byte_order::big_endian` means byte order is 4321, where the larger (big)
       numbered position comes first

  Example: Imagine the hexadecimal sequence in byte form of `DE AD BE EF`
    - When the bytes are read as a little-endian value, the bytes are read
      lowest byte first, producing the value: `0xEFBEADDE`
    - When the bytes are read as a big-endian value, the bytes are read highest
      byte first, producing the value: `0xDEADBEEF`

  `sdl::byte_order::native` is a compile-time constant of  that corresponds to
   the byte order used by the processor type it was compiled for.

  `sdl::byte_order::native` is `byte_order::little_endian` for x86, x64, and
   similar systems that use the little endian byte order.
  `sdl::byte_order::native` is `byte_order::big_endian` for PowerPC and similar
   systems that use the big endian byte order.

  @{
*/

//! The types of endianness
enum class byte_order {
    //! Litte endian
    little_endian = SDL_LIL_ENDIAN,
    //! Big endian
    big_endian = SDL_BIG_ENDIAN,
    //! Equal to either `byte_order::little_endian` or `byte_order::big_endian`
    native = SDL_BYTEORDER
};

namespace detail {

    template <byte_order From, byte_order To>
    struct endian_swapper {
        static_assert(
            From != To,
            "Something has gone wrong with endian_swapper specialisation");

        template <typename T>
        typename std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 2,
                                  T>
        operator()(T x) const {
            return SDL_Swap16(x);
        }

        template <typename T>
        typename std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 4,
                                  T>
        operator()(T x) const {
            return SDL_Swap32(x);
        }

        template <typename T>
        typename std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 8,
                                  T>
        operator()(T x) const {
            return SDL_Swap64(x);
        }

        float operator()(float x) const { return SDL_SwapFloat(x); }
    };

    template <byte_order Order>
    struct endian_swapper<Order, Order> {
        template <typename T>
        T&& operator()(T&& t) const {
            return std::forward<T>(t);
        }
    };

} // end namespace detail

//! Swap a value between byte orders
//!
//! @pre T is an integral type (signed or unsigned) or `float`
//! @note This function is a no-op if `From == To`
template <byte_order From, byte_order To = byte_order::native, typename T>
T byte_swap(T t) {
    return detail::endian_swapper<From, To>{}(t);
}

} // end namespace sdl

#endif // SDLXX_ENDIAN_HPP
