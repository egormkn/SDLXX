
#include <sdl++/version.hpp>

#include "catch.hpp"

TEST_CASE("sdl::version is correctly default constructed", "[version]") {
    constexpr sdl::version v{};

    REQUIRE(v.major == 0);
    REQUIRE(v.minor == 0);
    REQUIRE(v.patch == 0);
}

TEST_CASE("sdl::version is correctly list initialized", "[version]") {
    constexpr sdl::version v{1, 2, 3};

    REQUIRE(v.major == 1);
    REQUIRE(v.minor == 2);
    REQUIRE(v.patch == 3);
}

TEST_CASE("sdl::version relational operators work correctly", "[version]") {
    constexpr auto v1 = sdl::version{1, 2, 3};
    constexpr auto v2 = sdl::version{3, 2, 1};

    REQUIRE_FALSE(v1 == v2);
    REQUIRE_FALSE(v2 == v1);
    REQUIRE(v1 == v1);

    REQUIRE(v1 != v2);
    REQUIRE(v2 != v1);
    REQUIRE_FALSE(v1 != v1);

    REQUIRE(v1 < v2);
    REQUIRE_FALSE(v2 < v1);
    REQUIRE_FALSE(v1 < v1);

    REQUIRE(v1 <= v2);
    REQUIRE_FALSE(v2 <= v1);
    REQUIRE(v1 <= v1);

    REQUIRE_FALSE(v1 > v2);
    REQUIRE(v2 > v1);
    REQUIRE_FALSE(v1 > v1);

    REQUIRE_FALSE(v1 >= v2);
    REQUIRE(v2 >= v1);
    REQUIRE(v1 >= v1);
}

TEST_CASE("SDL_*_VERSION macros are wrapped correctly", "[version]") {
    constexpr auto v = sdl::get_compiled_version();

    REQUIRE(v.major == SDL_MAJOR_VERSION);
    REQUIRE(v.minor == SDL_MINOR_VERSION);
    REQUIRE(v.patch == SDL_PATCHLEVEL);
}

TEST_CASE("SDL_GetVersion() is wrapped correctly", "[version]") {
    const auto cpp_ver = sdl::get_linked_version();
    SDL_version c_ver;
    SDL_GetVersion(&c_ver);

    REQUIRE(c_ver.major == cpp_ver.major);
    REQUIRE(c_ver.minor == cpp_ver.minor);
    REQUIRE(c_ver.patch == cpp_ver.patch);
}

TEST_CASE("SDL_GetRevision() is wrapped correctly", "[version]") {
    const auto cpp_rev = sdl::get_revision();
    const auto c_rev = SDL_GetRevision();

    REQUIRE(std::string(cpp_rev) == std::string(c_rev));
}

TEST_CASE("SDL_GetRevisionNum() is wrapped correctly", "[version]") {
    REQUIRE(sdl::get_revision_number() == SDL_GetRevisionNumber());
}
