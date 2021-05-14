#include "sdlxx/core/color.h"

using namespace sdlxx::core;

Color::Color(uint32_t color)
    : r((color >> 16) & 0xFF), g((color >> 8) & 0xFF), b(color & 0xFF), a(0xFF) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

const Color Color::BLACK = 0x000000;
const Color Color::RED = 0xFF0000;
const Color Color::GREEN = 0x00FF00;
const Color Color::YELLOW = 0xFFFF00;
const Color Color::BLUE = 0x0000FF;
const Color Color::MAGENTA = 0xFF00FF;
const Color Color::CYAN = 0x00FFFF;
const Color Color::WHITE = 0xFFFFFF;
const Color Color::TRANSPARENT = {0, 0, 0, 0};
