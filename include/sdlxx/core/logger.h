#ifndef LOGGER_INCLUDED
#define LOGGER_INCLUDED

// Logger class from Professional C++ programming
// Modified by EgorMKN

// TODO: Rewrite

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <mutex>

// Definition of a thread-safe singleton logger class
class Logger {
public:
    enum Level {
        DEBUG,
        INFO,
        WARNING
    };

    // Returns a reference to the singleton Logger object
    static Logger &instance() {
        static Cleanup cleanup;

        lock_guard<mutex> guard(sMutex);
        if(pInstance == nullptr) {
            pInstance = new Logger();
        }
        return *pInstance;
    }

    template <typename T>
    friend Logger& operator<<(Logger& logger, const T& value) {
        std::lock_guard<std::mutex> guard(sMutex);
        std::string l;
        switch (logger.level) {
            case Level::DEBUG:
                l = "DEBUG";
                break;
            case Level::INFO:
                l = "INFO";
                break;
            default:
                l = "DEBUG";
        }
        logger.logHelper(value, l);
        return logger;
    }

    friend Logger& operator<<(Logger& logger, Level level) {
        std::lock_guard<std::mutex> guard(sMutex);
        logger.level = level;
        return logger;
    }

protected:
    // Static variable for the one-and-only instance
    static Logger *pInstance = nullptr;;

    Level level = Level::DEBUG;

    // Data member for the output stream
    std::ostream& stream = std::cout;

// Embedded class to make sure the single Logger
// instance gets deleted on program shutdown.
    friend class Cleanup;

    class Cleanup {
    public:
        ~Cleanup() {
            lock_guard<mutex> guard(Logger::sMutex);
            delete Logger::pInstance;
            Logger::pInstance = nullptr;
        }
    };

    // Logs message. The thread should own a lock on sMutex
    // before calling this function.
    void logHelper(const std::string &inMessage, const std::string &inLogLevel) {
        stream << inLogLevel << ": " << inMessage << endl;
    }

private:
    Logger();

    virtual ~Logger() = default;

    Logger(const Logger &) {
        cout << endl << "New logger created" << endl;
    }

    Logger &operator=(const Logger &);

    static std::mutex sMutex;
};
#endif //LOGGER_INCLUDED
