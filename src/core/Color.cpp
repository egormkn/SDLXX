#include <sdlxx/core/Color.h>

using namespace sdlxx::core;

Color::Color() : r(0), g(0), b(0), a(255) {}

Color::Color(uint32_t color)
    : a((color >> 24) & 0xFF),
      r((color >> 16) & 0xFF),
      g((color >> 8) & 0xFF),
      b(color & 0xFF) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : r(r), g(g), b(b), a(a) {}

Color Color::black = 0x000000;
Color Color::red = 0xFF0000;
Color Color::green = 0x00FF00;
Color Color::yellow = 0xFFFF00;
Color Color::blue = 0x0000FF;
Color Color::magenta = 0xFF00FF;
Color Color::cyan = 0x00FFFF;
Color Color::white = 0xFFFFFF;
