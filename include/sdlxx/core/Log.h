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
