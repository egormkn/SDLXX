#include <sdlxx/core/Color.h>

using namespace sdlxx::core;

Color::Color() : red(0), green(0), blue(0), alpha(255) {}

Color::Color(uint32_t color)
    : alpha((color >> 24) & 0xFF),
      red((color >> 16) & 0xFF),
      green((color >> 8) & 0xFF),
      blue(color & 0xFF) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : red(r), green(g), blue(b), alpha(a) {}
