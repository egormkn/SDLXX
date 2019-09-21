#include <sstream>
#include "Exception.h"

SDLXX::Exception::Exception() :
        exception(), msg("Error") {}

SDLXX::Exception::Exception(const std::string &m) :
        exception(), msg(m) {}

SDLXX::Exception::Exception(const std::string &m, const std::string &e) :
        exception() {
    std::stringstream s;
    s << m << ": " << e;
    msg = s.str();
}

SDLXX::Exception::Exception(const SDLXX::Exception &other) :
        exception(), msg(other.what()) {}

SDLXX::Exception::~Exception() {}

const char *SDLXX::Exception::what() const noexcept {
    return msg.c_str();
}