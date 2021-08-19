
#include <sdl++/init.hpp>

#include "catch.hpp"

namespace {

inline void expect_initted(uint32_t flags) {
    REQUIRE(SDL_WasInit(flags) != SDL_FALSE);
}

inline void expect_not_initted(uint32_t flags = SDL_INIT_EVERYTHING) {
    REQUIRE(SDL_WasInit(flags) == SDL_FALSE);
}
}

TEST_CASE("sdl::init_flags behave as expected", "[init]") {
    sdl::init_flags f = sdl::init_flags::timer | sdl::init_flags::audio;

    REQUIRE(sdl::flag_is_set(f, sdl::init_flags::audio));
    REQUIRE_FALSE(sdl::flag_is_set(f, sdl::init_flags::video));
}

TEST_CASE("Can create an init_guard from OR'd flags", "[init]") {
    expect_not_initted();

    {
        sdl::init_guard guard{sdl::init_flags::events | sdl::init_flags::timer};

        expect_initted(SDL_INIT_EVENTS | SDL_INIT_TIMER);
    }

    expect_not_initted();
}

TEST_CASE("Can create an init_guard from an initializer_list of flags",
          "[init]") {
    expect_not_initted();

    {
        sdl::init_guard guard{sdl::init_flags::events, sdl::init_flags::timer};

        expect_initted(SDL_INIT_EVENTS | SDL_INIT_TIMER);
    }

    expect_not_initted();
}

TEST_CASE("Can create a subsystem_init_guard", "[init]") {
    expect_not_initted();

    {
        sdl::subsystem_init_guard guard{sdl::init_flags::timer |
                                        sdl::init_flags::events};

        expect_initted(SDL_INIT_EVENTS | SDL_INIT_TIMER);
    }

    expect_not_initted();
}

TEST_CASE("Can copy a subsystem_init_guard", "[init]") {
    expect_not_initted();

    auto p1 = new sdl::subsystem_init_guard(sdl::init_flags::events);

    expect_initted(SDL_INIT_EVENTS);

    {
        auto p2 = *p1;
        expect_initted(SDL_INIT_EVENTS);

        delete p1;

        expect_initted(SDL_INIT_EVENTS);
    }

    expect_not_initted();
}

TEST_CASE("Can assign a subsystem_init_guard", "[init]") {
    expect_not_initted();

    {
        sdl::subsystem_init_guard g1{sdl::init_flags::events};
        expect_initted(SDL_INIT_EVENTS);

        {
            sdl::subsystem_init_guard g2{sdl::init_flags::timer};
            expect_initted(SDL_INIT_TIMER);

            g1 = g2;
        }

        expect_not_initted(SDL_INIT_EVENTS);
        expect_initted(SDL_INIT_TIMER);
    }

    expect_not_initted();
}
