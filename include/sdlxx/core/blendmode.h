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

/**
 * \file
 * \brief Header for the BlendMode enumeration that lists available blend modes.
 */

#ifndef SDLXX_CORE_BLENDMODE_H
#define SDLXX_CORE_BLENDMODE_H

#include "sdlxx/core/utils/bitmask.h"

namespace sdlxx {

/**
 * \brief An enumeration that lists blend modes used in Renderer::Copy() and drawing operations.
 *
 * Additional custom blend modes can be returned by ComposeCustomBlendMode()
 *
 * \upstream SDL_BlendMode
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
};

/**
 * \brief The blend operation used when combining source and destination pixel components.
 *
 * \upstream SDL_BlendOperation
 */
enum class BlendOperation {
  ADD = 0x1,          /**< dst + src: supported by all renderers */
  SUBTRACT = 0x2,     /**< dst - src : supported by D3D9, D3D11, OpenGL, OpenGLES */
  REV_SUBTRACT = 0x3, /**< src - dst : supported by D3D9, D3D11, OpenGL, OpenGLES */
  MINIMUM = 0x4,      /**< min(dst, src) : supported by D3D11 */
  MAXIMUM = 0x5       /**< max(dst, src) : supported by D3D11 */
};

/**
 * \brief The normalized factor used to multiply pixel components.
 *
 * \upstream SDL_BlendFactor
 */
enum class BlendFactor {
  ZERO = 0x1,                /**< 0, 0, 0, 0 */
  ONE = 0x2,                 /**< 1, 1, 1, 1 */
  SRC_COLOR = 0x3,           /**< srcR, srcG, srcB, srcA */
  ONE_MINUS_SRC_COLOR = 0x4, /**< 1-srcR, 1-srcG, 1-srcB, 1-srcA */
  SRC_ALPHA = 0x5,           /**< srcA, srcA, srcA, srcA */
  ONE_MINUS_SRC_ALPHA = 0x6, /**< 1-srcA, 1-srcA, 1-srcA, 1-srcA */
  DST_COLOR = 0x7,           /**< dstR, dstG, dstB, dstA */
  ONE_MINUS_DST_COLOR = 0x8, /**< 1-dstR, 1-dstG, 1-dstB, 1-dstA */
  DST_ALPHA = 0x9,           /**< dstA, dstA, dstA, dstA */
  ONE_MINUS_DST_ALPHA = 0xA  /**< 1-dstA, 1-dstA, 1-dstA, 1-dstA */
};

/**
 * \brief Create a custom blend mode, which may or may not be supported by a given renderer
 *
 * \param src_color_factor source color factor
 * \param dst_color_factor destination color factor
 * \param color_operation color operation
 * \param src_alpha_factor source alpha factor
 * \param dst_alpha_factor destination alpha factor
 * \param alpha_operation alpha operation
 *
 * The result of the blend mode operation will be:
 *     dstRGB = dstRGB * dstColorFactor colorOperation srcRGB * srcColorFactor
 * and
 *     dstA = dstA * dstAlphaFactor alphaOperation srcA * srcAlphaFactor
 *
 * \upstream SDL_ComposeCustomBlendMode
 */
BitMask<BlendMode> ComposeCustomBlendMode(
    BlendFactor src_color_factor, BlendFactor dst_color_factor, BlendOperation color_operation,
    BlendFactor src_alpha_factor, BlendFactor dst_alpha_factor, BlendOperation alpha_operation);

}  // namespace sdlxx

ENABLE_BITMASK_OPERATORS(sdlxx::BlendMode);

#endif  // SDLXX_CORE_BLENDMODE_H
