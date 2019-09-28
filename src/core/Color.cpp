#include <sdlxx/core/Color.h>
// #include <sdlxx/core/Utils.h>

using namespace sdlxx::core;

Color::Color() : red(0), green(0), blue(0), alpha(255) {}

Color::Color(uint32_t color_mask)
    : alpha((color_mask >> 24) & 0xFF),
      red((color_mask >> 16) & 0xFF),
      green((color_mask >> 8) & 0xFF),
      blue(color_mask & 0xFF) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : red(r), green(g), blue(b), alpha(a) {}

Color Color::operator+(const Color& color) const {
  int tmp = 0;

  uint8_t tmpR = 0;
  tmp = this->red + color.red;
  if (tmp > 255) tmpR = 255;
  if (tmp < 0) tmpR = 0;

  uint8_t tmpG = 0;
  tmp = this->green + color.green;
  if (tmp > 255) tmpG = 255;
  if (tmp < 0) tmpG = 0;

  uint8_t tmpB = 0;
  tmp = this->blue + color.blue;
  if (tmp > 255) tmpB = 255;
  if (tmp < 0) tmpB = 0;

  uint8_t tmpA = 255;
  if (this->alpha == color.alpha) tmpA = this->alpha;

  return {tmpR, tmpG, tmpB, tmpA};
}

Color Color::operator-(const Color& color) const {
  int tmp = 0;

  uint8_t tmpR = 0;
  tmp = this->red - color.red;
  if (tmp > 255) tmpR = 255;
  if (tmp < 0) tmpR = 0;

  uint8_t tmpG = 0;
  tmp = this->green - color.green;
  if (tmp > 255) tmpG = 255;
  if (tmp < 0) tmpG = 0;

  uint8_t tmpB = 0;
  tmp = this->blue - color.blue;
  if (tmp > 255) tmpB = 255;
  if (tmp < 0) tmpB = 0;

  uint8_t tmpA = 255;
  if (this->alpha == color.alpha) tmpA = this->alpha;

  Color result(tmpR, tmpG, tmpB, tmpA);
  return result;
}

bool Color::operator==(const Color& color) const {
  return ((this->red == color.red) && (this->green == color.green) &&
          (this->blue == color.blue) && (this->alpha == color.alpha));
}

bool Color::operator!=(const Color& color) const {
  return ((this->red != color.red) && (this->green != color.green) &&
          (this->blue != color.blue) && (this->alpha != color.alpha));
}
