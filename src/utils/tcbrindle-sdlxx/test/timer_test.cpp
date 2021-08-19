
#include <sdl++/timer.hpp>

#include "SDL.h"

#include "catch.hpp"

using namespace std::chrono_literals;

TEST_CASE("SDL_timer.h is wrapped correctly", "[timer]") {
    SDL_Init(SDL_INIT_TIMER);

    SECTION("sdl::clock works correctly") {
        auto t1 = SDL_GetTicks();
        auto t2 = sdl::clock::now();

        REQUIRE(t1 <= t2.time_since_epoch().count());
        REQUIRE(sdl::duration(t1) <= t2.time_since_epoch());
    }

    SECTION("SDL_GetPerformanceCounter() is wrapped correctly") {
        auto c1 = SDL_GetPerformanceCounter();
        auto c2 = sdl::get_performance_counter();

        REQUIRE(c1 <= c2);
    }

    SECTION("SDL_GetPerformanceFrequency() is wrapped correctly") {
        REQUIRE(sdl::get_performance_frequency() ==
                SDL_GetPerformanceFrequency());
    }

    SECTION("SDL_Delay() is wrapped correctly") {
        auto t1 = SDL_GetTicks();

        sdl::delay(25ms);

        auto t2 = SDL_GetTicks();

        REQUIRE(t2 >= t1 + 25);
    }

    SECTION("Timeout callbacks work correctly") {
        int call_count = 0;
        {
            auto t = sdl::make_timeout(10ms, [&call_count](auto) {
                call_count++;
                return 10ms;
            });

            // Allow enough time for the callback to be called twice, with a
            // little leeway
            SDL_Delay(25);
        }

        // Delay() is not accurate, so in fact we might have had more calls
        REQUIRE(call_count >= 2);

        int call_count2 = call_count;

        // Delay again to make sure the callback has been removed
        SDL_Delay(25);

        REQUIRE(call_count == call_count2);
    }

    SDL_Quit();
}
