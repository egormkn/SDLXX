/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer
  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgement in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * @file Log.h
 * @author Egor Makarenko
 * @brief Class that represents the logger
 */

#pragma once

#ifndef SDLXX_CORE_LOG_H
#define SDLXX_CORE_LOG_H

#include <string>

namespace sdlxx::core {

/**
 * @brief Class that represents the logger
 */
class Log {
public:
  static void error(std::string msg);

  static void warning(std::string msg);

  static void info(std::string msg);

  static void debug(std::string msg);

  static void raw(std::string msg);

  static void verbose(std::string msg);

  static void debugMode(bool option);

  static void verboseMode(bool option);

  static void newline();

private:
  static bool isDebugMode;    ///< Tells if we're on debug mode.
  static bool isVerboseMode;  ///< Tells if we're on verbose mode.

  static bool haveEscapeCodes;

  static void clearLine();
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_LOG_H
