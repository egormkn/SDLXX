#include <sdlxx/core/Color.h>
#include <sdlxx/core/Utils.h>

sdlxx::core::Color::Color() : red(0), green(0), blue(0), alpha(255) {}

sdlxx::core::Color::Color(uint32_t color_mask) {
    this->red = (uint8_t) ((color_mask >> 16) & 0xFF);
    this->green = (uint8_t) ((color_mask >> 8) & 0xFF);
    this->blue = (uint8_t) (color_mask & 0xFF);
    this->alpha = 255;
}

sdlxx::core::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : red(r), green(g), blue(b), alpha(a) {}

sdlxx::core::Color::Color(std::string &colorName) {
    uint8_t r, g, b;

    if(colorName == "white") {
        r = 255;
        g = 255;
        b = 255;
    } else if(colorName == "black") {
        r = 0;
        g = 0;
        b = 0;
    } else if(colorName == "red") {
        r = 255;
        g = 0;
        b = 0;
    } else if(colorName == "green") {
        r = 0;
        g = 255;
        b = 0;
    } else if(colorName == "blue") {
        r = 0;
        g = 0;
        b = 255;
    } else if(colorName == "cyan") {
        r = 0;
        g = 255;
        b = 255;
    } else if(colorName == "yellow") {
        r = 255;
        g = 255;
        b = 0;
    } else if(colorName == "magenta") {
        r = 255;
        g = 0;
        b = 255;
    }

    this->red = r;
    this->blue = b;
    this->green = g;
    this->alpha = 255;
}

sdlxx::core::Color sdlxx::core::Color::operator+(const sdlxx::core::Color &color) const {
    int tmp = 0;

    uint8_t tmpR = 0;
    tmp = this->red + color.red;
    if(tmp > 255) tmpR = 255;
    if(tmp < 0) tmpR = 0;

    uint8_t tmpG = 0;
    tmp = this->green + color.green;
    if(tmp > 255) tmpG = 255;
    if(tmp < 0) tmpG = 0;

    uint8_t tmpB = 0;
    tmp = this->blue + color.blue;
    if(tmp > 255) tmpB = 255;
    if(tmp < 0) tmpB = 0;

    uint8_t tmpA = 255;
    if(this->alpha == color.alpha)
        tmpA = this->alpha;

    Color result(tmpR, tmpG, tmpB, tmpA);
    return result;
}

sdlxx::core::Color sdlxx::core::Color::operator-(const sdlxx::core::Color &color) const {
    int tmp = 0;

    uint8_t tmpR = 0;
    tmp = this->red - color.red;
    if(tmp > 255) tmpR = 255;
    if(tmp < 0) tmpR = 0;

    uint8_t tmpG = 0;
    tmp = this->green - color.green;
    if(tmp > 255) tmpG = 255;
    if(tmp < 0) tmpG = 0;

    uint8_t tmpB = 0;
    tmp = this->blue - color.blue;
    if(tmp > 255) tmpB = 255;
    if(tmp < 0) tmpB = 0;

    uint8_t tmpA = 255;
    if(this->alpha == color.alpha)
        tmpA = this->alpha;

    Color result(tmpR, tmpG, tmpB, tmpA);
    return result;
}

bool sdlxx::core::Color::operator==(const Color &color) const {
    return ((this->red == color.red) &&
            (this->green == color.green) &&
            (this->blue == color.blue) &&
            (this->alpha == color.alpha));
}

bool sdlxx::core::Color::operator!=(const Color &color) const {
    return ((this->red != color.red) &&
            (this->green != color.green) &&
            (this->blue != color.blue) &&
            (this->alpha != color.alpha));
}

uint8_t sdlxx::core::Color::r() const {
    return (this->red);
}

uint8_t sdlxx::core::Color::g() const {
    return (this->green);
}

uint8_t sdlxx::core::Color::b() const {
    return (this->blue);
}

uint8_t sdlxx::core::Color::a() const {
    return (this->alpha);
}

void sdlxx::core::Color::randomize() {
    this->red = Utils::Random::between(0, 255);
    this->green = Utils::Random::between(0, 255);
    this->blue = Utils::Random::between(0, 255);
}

void sdlxx::core::Color::randomizeAlpha() {
    this->alpha = Utils::Random::between(0, 255);
}

void sdlxx::core::Color::invert(bool R, bool G, bool B) {
    if(R) this->red = (255 - this->red);
    if(G) this->green = (255 - this->green);
    if(B) this->blue = (255 - this->blue);
}

