
#include <sdl++/blendmode.hpp>

#include "catch.hpp"

TEST_CASE("SDL_blendmode.h is wrapped correctly", "[blendmode]") {
    // Not much we can actually test...!
    REQUIRE(SDL_BLENDMODE_ADD ==
              static_cast<SDL_BlendMode>(sdl::blend_mode::add));
    REQUIRE(SDL_BLENDMODE_BLEND ==
              static_cast<SDL_BlendMode>(sdl::blend_mode::blend));
    REQUIRE(SDL_BLENDMODE_MOD ==
              static_cast<SDL_BlendMode>(sdl::blend_mode::mod));
    REQUIRE(SDL_BLENDMODE_NONE ==
              static_cast<SDL_BlendMode>(sdl::blend_mode::none));
}
