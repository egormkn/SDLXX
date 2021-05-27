/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer
  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgement in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the BlendMode enum that represents available blend modes.
 */

#pragma once

#ifndef SDLXX_CORE_BLENDMODE_H
#define SDLXX_CORE_BLENDMODE_H

namespace sdlxx::core {

/**
 * \brief The blend mode used in Renderer::Copy() and drawing operations.
 */
enum class BlendMode {
  NONE = 0x00000000,  /**< no blending
                       dstRGBA = srcRGBA */
  BLEND = 0x00000001, /**< alpha blending
                       dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
                       dstA = srcA + (dstA * (1-srcA)) */
  ADD = 0x00000002,   /**< additive blending
                       dstRGB = (srcRGB * srcA) + dstRGB
                       dstA = dstA */
  MOD = 0x00000004,   /**< color modulate
                       dstRGB = srcRGB * dstRGB
                       dstA = dstA */
  MUL = 0x00000008,   /**< color multiply
                       dstRGB = (srcRGB * dstRGB) + (dstRGB * (1-srcA))
                       dstA = (srcA * dstA) + (dstA * (1-srcA)) */
  INVALID = 0x7FFFFFFF

  /* Additional custom blend modes can be returned by SDL_ComposeCustomBlendMode() */

};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_BLENDMODE_H
