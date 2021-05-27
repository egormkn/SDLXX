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
 * \file
 * \brief Header for the Log class that represents the logger.
 */

#pragma once

#ifndef SDLXX_CORE_LOG_H
#define SDLXX_CORE_LOG_H

#include <iostream>
#include <string>

namespace sdlxx::core {

/**
 * \brief A class that represents the logger.
 */
class Log {
public:
  enum class Verbosity { TRACE, DEBUG, INFO, WARNING, ERROR, FATAL };

  static void Trace(const std::string& message);

  static void Debug(const std::string& message);

  static void Info(const std::string& message);

  static void Warning(const std::string& message);

  static void Error(const std::string& message);

  static void Fatal(const std::string& message);

  static void SetVerbosity(Verbosity new_verbosity);

private:
  static Verbosity verbosity;
  static bool have_escape_codes;

  static void Print(Verbosity verbosity, const std::string& message,
                    std::ostream& stream = std::cout);
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_LOG_H
