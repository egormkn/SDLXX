#include "sdlxx/core/exception.h"

using namespace sdlxx::core;

Exception::Exception(const std::string& message) : message(message) {}

const char* Exception::what() const noexcept { return message.c_str(); }
