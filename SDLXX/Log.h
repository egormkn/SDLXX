#ifndef SDLXX_LOG_H
#define SDLXX_LOG_H

#include <string>

namespace SDLXX {
    class Log {
    public:
        static void error(std::string msg);

        static void warning(std::string msg);

        static void log(std::string msg);

        static void raw(std::string msg);

        static void debug(std::string msg);

        static void verbose(std::string msg);

        static void debugMode(bool option);

        static void verboseMode(bool option);

        static void newline();

    private:
        static bool isDebugMode;     ///< Tells if we're on debug mode.
        static bool isVerboseMode;   ///< Tells if we're on verbose mode.

        static bool haveEscapeCodes;

        static void clearLine();
    };
}

#endif //SDLXX_LOG_H
