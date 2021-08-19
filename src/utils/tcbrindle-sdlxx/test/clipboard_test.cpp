
#include <sdl++/clipboard.hpp>

#include "catch.hpp"

TEST_CASE("SDL_clipboard.h is wrapped correctly", "clipboard") {

    SDL_Init(SDL_INIT_VIDEO);

    constexpr const char test_str[] = u8"SDL Clipboard test \u2713";

    SECTION("Clipboard text can be read") {
        int r = SDL_SetClipboardText(test_str);
        if (r != 0) { throw std::runtime_error(SDL_GetError()); }

        SECTION("SDL_HasClipboardText() is wrapped correctly") {
            REQUIRE(sdl::has_clipboard_text());
        }

        SECTION("SDL_GetClipboardText() is wrapped correctly") {
            REQUIRE(sdl::get_clipboard_text() == test_str);
        }
    }

    SECTION("Clipboard text can be set") {
        sdl::set_clipboard_text(test_str);
        REQUIRE(SDL_strcmp(SDL_GetClipboardText(), test_str) == 0);

        sdl::set_clipboard_text(sdl::string(test_str));
        REQUIRE(SDL_strcmp(SDL_GetClipboardText(), test_str) == 0);
    }

    // SDL_SetClipboardText(nullptr);
    SDL_Quit();
}
