#include <sdlxx/ttf/Text.h>

using namespace sdlxx::ttf;

Text::Text(const std::string& text) : Surface(nullptr) {}

Text::Text(void* surface_ptr) : Surface(surface_ptr) {}
