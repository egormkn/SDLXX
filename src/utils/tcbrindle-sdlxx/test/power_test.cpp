
#include <sdl++/power.hpp>

#include "SDL.h"

#include "catch.hpp"

using namespace std::chrono_literals;

TEST_CASE("SDL_PowerState is wrapped correctly", "[power]") {
    const auto cast = [](auto s) { return static_cast<SDL_PowerState>(s); };

    REQUIRE(SDL_POWERSTATE_UNKNOWN == cast(sdl::power_state::unknown));
    REQUIRE(SDL_POWERSTATE_ON_BATTERY == cast(sdl::power_state::on_battery));
    REQUIRE(SDL_POWERSTATE_NO_BATTERY == cast(sdl::power_state::no_battery));
    REQUIRE(SDL_POWERSTATE_CHARGING == cast(sdl::power_state::charging));
    REQUIRE(SDL_POWERSTATE_CHARGED == cast(sdl::power_state::charged));
}

TEST_CASE("sdl::power_info is correctly default-constructed", "[power]") {
    auto p = sdl::power_info{};

    REQUIRE(p.state == sdl::power_state::unknown);
    REQUIRE(p.secs_left == sdl::nullopt);
    REQUIRE(p.percent_left == sdl::nullopt);
}

TEST_CASE("sdl::power_info relational operations are correctly defined",
          "[power]") {
    sdl::power_info p1{};
    sdl::power_info p2{sdl::power_state::on_battery, 3600s, 58};

    REQUIRE(p1 == p1);
    REQUIRE(p2 == p2);
    REQUIRE(p1 != p2);
}

TEST_CASE("SDL_GetPowerInfo() is wrapped correctly", "[power]") {
    SDL_Init(SDL_INIT_EVENTS);

    auto info = sdl::get_power_info();

    int c_secs, c_pct;
    auto c_state = SDL_GetPowerInfo(&c_secs, &c_pct);

    REQUIRE(c_state == static_cast<SDL_PowerState>(info.state));
    REQUIRE(c_secs == info.secs_left.value_or(-1s).count());
    REQUIRE(c_pct == info.percent_left.value_or(-1));

    SDL_Quit();
}
