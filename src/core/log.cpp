#include "sdlxx/core/log.h"

#include <iostream>
#include <sstream>

#include <SDL_log.h>

using namespace sdlxx::core;

using Verbosity = Log::Verbosity;

Verbosity Log::verbosity = Verbosity::TRACE;
bool Log::have_escape_codes = false;

void Log::Trace(const std::string& message) { return Print(Verbosity::TRACE, message); }

void Log::Debug(const std::string& message) { return Print(Verbosity::DEBUG, message); }

void Log::Info(const std::string& message) { return Print(Verbosity::INFO, message); }

void Log::Warning(const std::string& message) { return Print(Verbosity::WARNING, message); }

void Log::Error(const std::string& message) { return Print(Verbosity::ERROR, message); }

void Log::Fatal(const std::string& message) { return Print(Verbosity::FATAL, message); }

void Log::SetVerbosity(Verbosity new_verbosity) { verbosity = new_verbosity; }

void Log::Print(Verbosity verbosity, const std::string& message, std::ostream& stream) {
  stream << message << std::endl;
}
