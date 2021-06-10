#include "sdlxx/core/rectangle.h"

using namespace sdlxx;

constexpr Point Rectangle::GetOrigin() const { return {x, y}; }

constexpr Dimensions Rectangle::GetDimensions() const { return {width, height}; }
