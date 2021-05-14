#include <sdlxx/core/version.h>

using namespace sdlxx::core;

Version::Version(uint8_t major, uint8_t minor, uint8_t patch)
    : major(major), minor(minor), patch(patch) {}
