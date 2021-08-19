
#include <sdl++/endian.hpp>

#include "catch.hpp"

constexpr uint16_t u16 = 0xDEAD;
constexpr uint32_t u32 = 0xDEADBEEF;
constexpr uint64_t u64 = 0xDEADBEEFDEADBEEF;
const float f32 = *reinterpret_cast<const float*>(&u32);

TEST_CASE("SDL_BYTEORDER is wrapped correctly", "[endian]") {
    REQUIRE(static_cast<int>(sdl::byte_order::little_endian) == SDL_LIL_ENDIAN);
    REQUIRE(static_cast<int>(sdl::byte_order::big_endian) == SDL_BIG_ENDIAN);
    REQUIRE(static_cast<int>(sdl::byte_order::native) == SDL_BYTEORDER);
}

TEST_CASE("Swaps from LE to native work correctly", "[endian]") {
    const auto u16le = sdl::byte_swap<sdl::byte_order::little_endian>(u16);
    const auto u32le = sdl::byte_swap<sdl::byte_order::little_endian>(u32);
    const auto u64le = sdl::byte_swap<sdl::byte_order::little_endian>(u64);
    const auto f32le = sdl::byte_swap<sdl::byte_order::little_endian>(f32);

    REQUIRE(u16le == SDL_SwapLE16(u16));
    REQUIRE(u32le == SDL_SwapLE32(u32));
    REQUIRE(u64le == SDL_SwapLE64(u64));
    REQUIRE(f32le == SDL_SwapFloatLE(f32));
}

TEST_CASE("Swaps from BE to native work correctly", "[endian]") {
    const auto u16be = sdl::byte_swap<sdl::byte_order::big_endian>(u16);
    const auto u32be = sdl::byte_swap<sdl::byte_order::big_endian>(u32);
    const auto u64be = sdl::byte_swap<sdl::byte_order::big_endian>(u64);
    const auto f32be = sdl::byte_swap<sdl::byte_order::big_endian>(f32);

    REQUIRE(u16be == SDL_SwapBE16(u16));
    REQUIRE(u32be == SDL_SwapBE32(u32));
    REQUIRE(u64be == SDL_SwapBE64(u64));
    REQUIRE(f32be == SDL_SwapFloatBE(f32));
}

TEST_CASE("Swaps from native to other endian work correctly", "[endian]") {
    auto swapper = [=](auto v) {
        constexpr sdl::byte_order other_endian =
            sdl::byte_order::native == sdl::byte_order::little_endian
                ? sdl::byte_order::big_endian
                : sdl::byte_order::little_endian;
        return sdl::byte_swap<sdl::byte_order::native, other_endian>(v);
    };

    REQUIRE(swapper(u16) == SDL_Swap16(u16));
    REQUIRE(swapper(u32) == SDL_Swap32(u32));
    REQUIRE(swapper(u64) == SDL_Swap64(u64));
    REQUIRE(swapper(f32) == SDL_SwapFloat(f32));
}
