#include "sdlxx/core/version.h"

#include <tuple>

using namespace sdlxx;

Version::Version(uint8_t major, uint8_t minor, uint8_t patch)
    : major(major), minor(minor), patch(patch) {}

bool Version::operator<(const Version& other) const {
  return std::tie(major, minor, patch) < std::tie(other.major, other.minor, other.patch);
}

bool Version::operator>(Version& other) const { return other < *this; }

bool Version::operator<=(Version& other) const { return !(other < *this); }

bool Version::operator>=(Version& other) const { return !(*this < other); }

bool Version::operator==(const Version& other) const {
  return major == other.major && minor == other.minor && patch == other.patch;
}

bool Version::operator!=(const Version& other) const { return !(*this == other); }
