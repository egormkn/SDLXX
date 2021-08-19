/*
  @file blendmode.hpp
  Header file declaring the sdl::blend_mode enumeration

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
#ifndef SDLXX_BLENDMODE_HPP
#define SDLXX_BLENDMODE_HPP

#include "SDL_blendmode.h"

namespace sdl {

//! The blend mode used in `sdl::renderer::copy()` and drawing operations.
//! @ingroup Render
enum class blend_mode {
    /*!
     No blending
     `dstRGBA = srcRGBA`
    */
    none = SDL_BLENDMODE_NONE,

    /*!
      alpha blending
      `dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))`
      `dstA = srcA + (dstA * (1-srcA))`
    */
    blend = SDL_BLENDMODE_BLEND,

    /*!
      Additive blending
      `dstRGB = (srcRGB * srcA) + dstRGB`
      `dstA = dstA`
    */
    add = SDL_BLENDMODE_ADD,

    /*!
      color modulate
      `dstRGB = srcRGB * dstRGB`
      `dstA = dstA`
    */
    mod = SDL_BLENDMODE_MOD
};

} // end namespace sdl

#endif // SDLXX_BLENDMODE_HPP
