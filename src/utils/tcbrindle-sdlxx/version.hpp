/*!
  @file version.hpp
  Functions and classes dealing with SDL versions

  @copyright (C) 2016 Tristan Brindle <t.c.brindle@gmail.com>
  @copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDLXX_VERSION_HPP
#define SDLXX_VERSION_HPP

#include "SDL_version.h"

#include "detail/relops.hpp"

#include <iostream>

namespace sdl {

/*!
 @defgroup Version Querying SDL version
 @{

 These functions are used to collect or display information about the version
 of SDL that is currently being used by the program or that it was compiled
 against. The version consists of three segments (X.Y.Z)

 - X = Major Version, which increments with massive changes, additions, and
     enhancements
 - Y = Minor Version, which increments with backwards-compatible changes to
     the major revision
 - Z = Patch level, which increments with fixes to the minor revision

 For example, the current version is 2.0.4

 The compile-time SDL version is available with the
 `sdl::get_compiled_version()` function. This is a `constexpr` function, and
 so could be used for conditional compilation with `std::enable_if()`.

 Alternatively, the compile-time SDL version is available via the
 `SDL_COMPILED_VERSION` macro, and the individual components via
 `SDL_MAJOR_VERSION`, `SDL_MINOR_VERSION` and `SDL_PATCH_VERSION` -- see the
 [C documentation](https://wiki.libsdl.org/CategoryVersion).
 */

/*!
 @brief Represents an SDL version number

 Represents the library's version as three levels: major revision
 (increments with massive changes, additions, and enhancements),
 minor revision (increments with backwards-compatible changes to the
 major revision), and patchlevel (increments with fixes to the minor
 revision).

 `sdl::version`s can be compared using the usual comparison operators, for
 example

 ```
 sdl::version v1{2, 0, 3};
 sdl::version v2{2, 0, 4};

 v1 < v2; // true
 ```

 and can be passed to a `std::ostream`

 ```
 sdl::version v = sdl::get_compiled_version();

 std::cout << "Compiled with SDL " << v << "\n";
 ```

 @sa `sdl::get_compiled_version()`
 @sa `sdl::get_linked_version()`
 */
struct version : SDL_version {
    //! Default-constructs an sdl::version to {0, 0, 0}
    constexpr version() : SDL_version{0, 0, 0} {}

    /*!
     Constructs an sdl::version from the given major, minor and patch levels
     @param major The major version number
     @param minor The minor version number
     @param patch The patch level
     @returns A newly constructed sdl::version
     */
    constexpr version(uint8_t major, uint8_t minor, uint8_t patch)
        : SDL_version{major, minor, patch} {}
};

//! @relates version
// TODO(C++14): use std::tie when marked constexpr in libstdc++
inline constexpr bool operator==(version lhs, version rhs) {
    return lhs.major == rhs.major && lhs.minor == rhs.minor &&
           lhs.patch == rhs.patch;
}

//! @relates version
// TODO(C++14): use std::tie when marked constexpr in libstdc++
inline constexpr bool operator<(version lhs, version rhs) {
    return lhs.major == rhs.major
               ? lhs.minor == rhs.minor ? lhs.patch < rhs.patch
                                        : lhs.minor < rhs.minor
               : lhs.major < rhs.major;
}

//! @relates version
inline std::ostream& operator<<(std::ostream& os, version v) {
    return os << int{v.major} << '.' << int{v.minor} << '.' << int{v.patch};
}

/*!
 Get the version of SDL that is linked against your program.

 If you are linking to SDL dynamically, then it is possible that the
 current version will be different than the version you compiled against.
 This function returns the current version, while `get_compiled_version()` is a
 function that tells you what version you compiled with.

 ```
 sdl::version compiled = sdl::get_compiled_version();
 sdl::version linked = sdl::get_linked_version();

 std::cout << "We compiled against SDL version " << compiled << "\n";
 std::cout << "But we linked against SDL version << linked << "\n";
 ```

 This function may be called safely at any time, even before sdl::init().

 @sa `sdl::get_compiled_version()`
 */
inline version get_linked_version() {
    version v{0, 0, 0};
    ::SDL_GetVersion(&v);
    return v;
}

/*!
 Determine SDL version program was compiled against.

 This function returns a sdl::version structure with the version of the
 library you compiled against. This is determined by what header the
 compiler uses. Note that if you dynamically linked the library, you might
 have a slightly newer or older version at runtime. That version can be
 determined with sdl::get_linked_version()

 @sa `sdl::version`
 @sa `sdl::get_linked_version()`
 */
inline constexpr version get_compiled_version() {
    return version{SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL};
}

/*!
 @brief Get the code revision of SDL that is linked against your program.

 @returns An arbitrary string (a hash value) uniquely identifying the
  exact revision of the SDL library in use, and is only useful in comparing
  against other revisions. It is NOT an incrementing number.
 */
inline const char* get_revision() { return ::SDL_GetRevision(); }

/*!
 Get the revision number of SDL that is linked against your program.

 @returns A number uniquely identifying the exact revision of the SDL
  library in use. It is an incrementing number based on commits to
  hg.libsdl.org.
 */
inline int get_revision_number() { return ::SDL_GetRevisionNumber(); }

//! @}

} // end namespace sdl

#endif // SDLXX_VERSION_HPP
