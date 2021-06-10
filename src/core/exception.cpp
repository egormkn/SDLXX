#include "sdlxx/core/exception.h"

#include <SDL_error.h>

using namespace sdlxx;

Exception::Exception(const std::string& message) : message(message + ": " + SDL_GetError()) {}

const char* Exception::what() const noexcept { return message.c_str(); }
