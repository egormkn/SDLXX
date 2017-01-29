#include "Exception.h"
#include <SDL_quit.h>

SDL::Exception::Exception() :
        exception(), msg(SDL_GetError()) {
    SDL_ClearError();
}

SDL::Exception::Exception(const std::string &m) :
        exception(), msg(m) {}

SDL::Exception::Exception(const std::string &m, const std::string &e) :
        exception() {
    std::stringstream s;
    s << m << ": " << e;
    msg = s.str();
}

SDL::Exception::Exception(const SDL::Exception &other) :
        exception(), msg(other.what()) {}

SDL::Exception::~Exception() {}

const char *SDL::Exception::what() const noexcept{
    return msg.c_str();
}