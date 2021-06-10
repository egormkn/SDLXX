#include "sdlxx/core/blendmode.h"

#include <SDL_blendmode.h>

#include "sdlxx/core/utils/bitmask.h"

using namespace sdlxx;

#define ASSERT_BLENDMODE(x) \
  static_assert(static_cast<SDL_BlendMode>(BlendMode::x) == SDL_BLENDMODE_##x);

ASSERT_BLENDMODE(NONE);
ASSERT_BLENDMODE(BLEND);
ASSERT_BLENDMODE(ADD);
ASSERT_BLENDMODE(MOD);
ASSERT_BLENDMODE(MUL);
ASSERT_BLENDMODE(INVALID);

#define ASSERT_BLENDOPERATION(x) \
  static_assert(static_cast<SDL_BlendOperation>(BlendOperation::x) == SDL_BLENDOPERATION_##x);

ASSERT_BLENDOPERATION(ADD);
ASSERT_BLENDOPERATION(SUBTRACT);
ASSERT_BLENDOPERATION(REV_SUBTRACT);
ASSERT_BLENDOPERATION(MINIMUM);
ASSERT_BLENDOPERATION(MAXIMUM);

#define ASSERT_BLENDFACTOR(x) \
  static_assert(static_cast<SDL_BlendFactor>(BlendFactor::x) == SDL_BLENDFACTOR_##x);

ASSERT_BLENDFACTOR(ZERO);
ASSERT_BLENDFACTOR(ONE);
ASSERT_BLENDFACTOR(SRC_COLOR);
ASSERT_BLENDFACTOR(ONE_MINUS_SRC_COLOR);
ASSERT_BLENDFACTOR(SRC_ALPHA);
ASSERT_BLENDFACTOR(ONE_MINUS_SRC_ALPHA);
ASSERT_BLENDFACTOR(DST_COLOR);
ASSERT_BLENDFACTOR(ONE_MINUS_DST_COLOR);
ASSERT_BLENDFACTOR(DST_ALPHA);
ASSERT_BLENDFACTOR(ONE_MINUS_DST_ALPHA);

BitMask<BlendMode> ComposeCustomBlendMode(
    BlendFactor src_color_factor, BlendFactor dst_color_factor, BlendOperation color_operation,
    BlendFactor src_alpha_factor, BlendFactor dst_alpha_factor, BlendOperation alpha_operation) {
  return BitMask<BlendMode>{
      SDL_ComposeCustomBlendMode(static_cast<SDL_BlendFactor>(src_color_factor),
                                 static_cast<SDL_BlendFactor>(dst_color_factor),
                                 static_cast<SDL_BlendOperation>(color_operation),
                                 static_cast<SDL_BlendFactor>(src_alpha_factor),
                                 static_cast<SDL_BlendFactor>(dst_alpha_factor),
                                 static_cast<SDL_BlendOperation>(alpha_operation))};
}
