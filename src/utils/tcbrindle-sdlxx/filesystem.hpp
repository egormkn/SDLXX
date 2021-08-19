/*
  @file filesystem.hpp
  Include file for filesystem SDL API functions
  @copyright (C) 2014-2016 Tristan Brindle <t.c.brindle@gmail.com>
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
#ifndef SDLXX_FILESYSTEM_HPP
#define SDLXX_FILESYSTEM_HPP

#include "SDL_filesystem.h"

#include "detail/wrapper.hpp"
#include "macros.hpp"
#include "stdinc.hpp"

namespace sdl {

/*!
  @defgroup Filesystem Filesystem Paths
  This category contains functions for getting commonly used paths such as the
  application directory and the user write directory.

  @{
*/

/*!
 Get the path where the application resides.

 Get the "base path". This is the directory where the application was run
 from, which is probably the installation directory, and may or may not
 be the process's current working directory.

 This returns an absolute path in UTF-8 encoding, and is guaranteed to
 end with a path separator ('\\' on Windows, '/' most other places).

 This is not necessarily a fast call, though, so you should
 call this once near startup and save the string if you need it.

 Some platforms can't determine the application's path, and on other
 platforms, this might be meaningless. In such cases, this function will
 return throw an `sdl::error` if exceptions are enabled.

  __Mac OS X and iOS Specific Functionality:__ If the application is in a
  ".app" bundle, this function returns the Resource directory (e.g.
  MyApp.app/Contents/Resources/). This behaviour can be overridden by adding a
  property to the Info.plist file. Adding a string key with the name
  `SDL_FILESYSTEM_BASE_DIR_TYPE` with a supported value will change the
  behaviour.

 @return String of base dir in UTF-8 encoding
 @throws sdl::error
*/
inline string get_base_path() {
    auto path = detail::c_call(::SDL_GetBasePath);
    SDLXX_CHECK(path != "");
    return path;
}

/*!
  Get the user-and-app-specific path where files can be written.

  Get the "pref dir". This is meant to be where users can write personal
  files (preferences and save games, etc) that are specific to your
  application. This directory is unique per user, per application.

  This function will decide the appropriate location in the native filesystem,
  create the directory if necessary, and return a string of the absolute
  path to the directory in UTF-8 encoding.

  On Windows, the string might look like:
  "C:\\Users\\bob\\AppData\\Roaming\\My Company\\My Program Name\\"

  On Linux, the string might look like:
   "/home/bob/.local/share/My Program Name/"

  On Mac OS X, the string might look like:
   "/Users/bob/Library/Application Support/My Program Name/"

  (etc.)

  You specify the name of your organization (if it's not a real organization,
  your name or an Internet domain you own might do) and the name of your
  application. These should be untranslated proper names.

  Both the org and app strings may become part of a directory name, so
  please follow these rules:

     - Try to use the same org string (including case-sensitivity) for
       all your applications that use this function.
     - Always use a unique app string for each one, and make sure it never
       changes for an app once you've decided on it.
     - Unicode characters are legal, as long as it's UTF-8 encoded, but...
     - ...only use letters, numbers, and spaces. Avoid punctuation like
       "Game Name 2: Bad Guy's Revenge!" ... "Game Name 2" is sufficient.

  This returns an absolute path in UTF-8 encoding, and is guaranteed to
  end with a path separator ('\\' on Windows, '/' most other places).

  This is not necessarily a fast call, though, so you should
  call this once near startup and save the string if you need it.

  You should assume the path returned by this function is the only safe
  place to write files (and that `sdl::get_base_path()`, while it might be
  writable, or even the parent of the returned path, aren't where you
  should be writing things).

  Some platforms can't determine the pref path, and on other
  platforms, this might be meaningless. In such cases, this function will throw
  an `sdl::error`.

  @param org The name of your organization.
  @param app The name of your application.
  @return UTF-8 string of user dir in platform-dependent notation. `nullopt`
          if there's a problem (creating directory failed, etc).
  @throws sdl::error

  \sa sdl::get_base_path()
 */
inline string get_pref_path(const char* org, const char* app) {
    auto path = detail::c_call(::SDL_GetPrefPath, org, app);
    SDLXX_CHECK(path != "");
    return path;
}

//! Overload of get_pref_path() taking strings
inline string get_pref_path(const string& org, const string& app) {
    auto path = detail::c_call(::SDL_GetPrefPath, org, app);
    SDLXX_CHECK(path != "");
    return path;
}

} // end namespace sdl

#endif // SDLXX_FILESYSTEM_HPP
