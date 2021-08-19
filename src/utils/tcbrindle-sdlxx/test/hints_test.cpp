
#include <sdl++/hints.hpp>

#include "SDL.h"

#include "catch.hpp"

#include <string>
#include <iostream>

using namespace std::string_literals;

TEST_CASE("SDL_hints.h is wrapped correctly", "[hints]") {

    SECTION("sdl::set_hint() with normal priority") {
        // Just pick a random hint which is documented as disabled by default
        REQUIRE(sdl::set_hint(sdl::hint::grab_keyboard, "1"));
        REQUIRE(SDL_GetHint(SDL_HINT_GRAB_KEYBOARD) == "1"s);
    }

    SECTION("sdl::set_hint() with varying priorities") {
        // Set hint with normal priority
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "test1");
        REQUIRE(SDL_GetHint(SDL_HINT_RENDER_DRIVER) == "test1"s);

        bool result = sdl::set_hint(sdl::hint::render_driver, "test2",
                                    sdl::hint_priority::hint_default);
        REQUIRE_FALSE(result);

        REQUIRE(SDL_GetHint(SDL_HINT_RENDER_DRIVER) == "test1"s);

        result = sdl::set_hint(sdl::hint::render_driver, "test3",
                               sdl::hint_priority::hint_normal);
        REQUIRE(result);
        REQUIRE(SDL_GetHint(SDL_HINT_RENDER_DRIVER) == "test3"s);

        result = sdl::set_hint(sdl::hint::render_driver, "test4",
                               sdl::hint_priority::hint_override);
        REQUIRE(result);
        REQUIRE(SDL_GetHint(SDL_HINT_RENDER_DRIVER) == "test4"s);
    }

    SECTION("SDL_GetHint() is wrapped correctly") {
        SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "1");

        REQUIRE(get_hint(sdl::hint::grab_keyboard) == "1"s);
    }

    SECTION("Hint callbacks work correctly") {
        // Note that there seems to be a bug in SDL, whereby the hint callback
        // will be called twice in response to SetHint, first with old_val and
        // new_val both equal to the old value, and then again with old_val and
        // new_val as you would expect them.
        // This is not an sdl++ bug as the same thing happens using the C API.

        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "test1");
        bool called = false;

        auto l = [&called](auto name, auto old_val, auto /* new_val */) {
            called = true;
            REQUIRE((name == sdl::hint::render_driver));
            REQUIRE((old_val == "test1"s));
            // REQUIRE(new_val == "test2");
        };

        {
            auto cb = sdl::add_hint_callback(sdl::hint::render_driver, l);

            SDL_SetHint(SDL_HINT_RENDER_DRIVER, "test2");

            REQUIRE(called);
            called = false;
        }

        // Ensure that the callback has been removed
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "test3");
        REQUIRE_FALSE(called);
    }

    SDL_ClearHints();
}

TEST_CASE("sdl::clear_hints() is wrapped correctly", "[hints]") {
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "test1");

    sdl::clear_hints();

    REQUIRE_FALSE(SDL_GetHint(SDL_HINT_RENDER_DRIVER));
}
