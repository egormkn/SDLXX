#include "Log.h"
#include <sstream>
#include <iostream>
#include <SDL_log.h>

bool SDLXX::Log::isDebugMode = false;
bool SDLXX::Log::isVerboseMode = true;

// std::ostream& Log::stdout       = std::cout;
// std::ostream& Log::stderr       = std::cout;
// bool          Log::isUsingFiles = false;

// Terminal escape codes.
//
// They are commands to the terminal
// (print the following text at color X, clear the screen, etc).
//
// Don't use this on files!

const std::string bold_red = "\e[1;31m";
const std::string red = "\e[0;31m";
const std::string bold_cyan = "\e[1;36m";
const std::string cyan = "\e[0;36m";
const std::string bold_green = "\e[1;32m";
const std::string green = "\e[0;32m";
const std::string bold_yellow = "\e[1;33m";
const std::string yellow = "\e[0;33m";
const std::string reset_color = "\e[0m";
const std::string clear_screen = "[H[2J";
const std::string clear_line = "\r\e[0K";

// Prefixes
const std::string errorPrefix = "Error:   ";
const std::string warningPrefix = "Warning: ";
const std::string debugPrefix = "Debug:   ";
const std::string verbosePrefix = "Verbose: ";

void SDLXX::Log::error(std::string msg) {
    std::cerr << errorPrefix << msg << std::endl;
    std::cout.flush();
}

void SDLXX::Log::warning(std::string msg) {
    std::cerr << warningPrefix << msg << std::endl;
    std::cout.flush();
}

void SDLXX::Log::log(std::string msg) {
    std::cout << msg << std::endl;
    std::cout.flush();
}

void SDLXX::Log::raw(std::string msg) {
    std::cout << msg;
    std::cout.flush();
}

void SDLXX::Log::debug(std::string msg) {
    if(isDebugMode)
        std::cerr << debugPrefix << msg << std::endl;
    std::cout.flush();
}

void SDLXX::Log::verbose(std::string msg) {
    if(isVerboseMode)
        std::cerr << verbosePrefix << msg << std::endl;
    std::cout.flush();
}

void SDLXX::Log::debugMode(bool option) {
    if(option == false) {
        isDebugMode = false;
        return;
    }

    isDebugMode = true;
    Log::debug("> Debug mode activated");
}

void SDLXX::Log::verboseMode(bool option) {
    if(!option) {
        isVerboseMode = false;
        return;
    }

    // Prints a nice logo
    isVerboseMode = true;
    Log::verbose("> Verbose Mode activated");
}

void SDLXX::Log::clearLine() {
    std::cout << clear_line;
    std::cout.flush();
}

void SDLXX::Log::newline() {
    std::cout << std::endl;
    std::cout.flush();
}
