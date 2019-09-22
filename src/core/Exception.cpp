#include <sstream>
#include <sdlxx/core/Exception.h>

sdlxx::core::Exception::Exception() :
        exception(), msg("Error") {}

sdlxx::core::Exception::Exception(const std::string &m) :
        exception(), msg(m) {}

sdlxx::core::Exception::Exception(const std::string &m, const std::string &e) :
        exception() {
    std::stringstream s;
    s << m << ": " << e;
    msg = s.str();
}

sdlxx::core::Exception::Exception(const sdlxx::core::Exception &other) :
        exception(), msg(other.what()) {}

sdlxx::core::Exception::~Exception() {}

const char *sdlxx::core::Exception::what() const noexcept {
    return msg.c_str();
}
