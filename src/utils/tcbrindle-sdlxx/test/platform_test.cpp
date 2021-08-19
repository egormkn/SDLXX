
#include <sdl++/platform.hpp>

#include "catch.hpp"

TEST_CASE("SDL_GetPlatform() is wrapped correctly", "[platform]") {
    REQUIRE(SDL_GetPlatform() == sdl::get_platform_name());
}
