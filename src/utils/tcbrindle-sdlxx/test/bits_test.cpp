
#include <sdl++/bits.hpp>

#include "catch.hpp"

TEST_CASE("SDL_MostSignificantBitIndex32() is wrapped correctly", "[bits]") {
    std::uint32_t val = 0x12345678;
    REQUIRE(SDL_MostSignificantBitIndex32(val) ==
              sdl::most_significant_bit_index(val));
}

TEST_CASE("sdl::most_significant_bit_index(0) == -1", "[bits]") {
    REQUIRE(sdl::most_significant_bit_index(0) == -1);
}
