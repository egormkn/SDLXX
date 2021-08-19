
#include <sdl++/cpuinfo.hpp>

#include "catch.hpp"

/*
 MSVC complains about comparing a real bool with an SDL_bool (which is an
 enum), so use this to shut it up
*/
static inline SDL_bool sbool(bool b) {
    return b ? SDL_TRUE : SDL_FALSE;
}


TEST_CASE("SDL_GetCPUCount() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sdl::get_cpu_count() == SDL_GetCPUCount());
}

TEST_CASE("SDL_GetCPUCachLineSize() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sdl::get_cpu_cache_line_size() == SDL_GetCPUCacheLineSize());
}

TEST_CASE("SDL_HasRDTSC() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_rdtsc()) == SDL_HasRDTSC());
}

TEST_CASE("SDL_HasAltiVec() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_altivec()) == SDL_HasAltiVec());
}

TEST_CASE("SDL_HasMMX() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_mmx()) == SDL_HasMMX());
}

TEST_CASE("SDL_Has3DNow() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_3dnow()) == SDL_Has3DNow());
}

TEST_CASE("SDL_HasSSE() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_sse()) == SDL_HasSSE());
}

TEST_CASE("SDL_HasSSE2() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_sse2()) == SDL_HasSSE2());
}

TEST_CASE("SDL_HasSSE3() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_sse3()) == SDL_HasSSE3());
}

TEST_CASE("SDL_HasSSE41() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_sse41()) == SDL_HasSSE41());
}

TEST_CASE("SDL_HasSSE42() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_sse42()) == SDL_HasSSE42());
}

TEST_CASE("SDL_HasAVX() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_avx()) == SDL_HasAVX());
}

TEST_CASE("SDL_HasAVX2() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sbool(sdl::cpu_has_avx2()) == SDL_HasAVX2());
}

TEST_CASE("SDL_GetSystemRam() is wrapped correctly", "[cpuinfo]") {
    REQUIRE(sdl::get_system_ram() == SDL_GetSystemRAM());
}
