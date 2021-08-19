/**
  @file log.hpp

  Simple DirectMedia Layer C++ Bindings
  @copyright (C) 2014-2016 Tristan Brindle <t.c.brindle@gmail.com>

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

#ifndef SDLXX_LOG_HPP
#define SDLXX_LOG_HPP

#include "detail/wrapper.hpp"
#include "macros.hpp"
#include "stdinc.hpp"

#include "SDL_log.h"

namespace sdl {

/*!
 @defgroup Log Log Handling

 This category contains functions for handling simple log messages with
 categories and priorities.

 Simple log messages with categories and priorities.

 Here's where the messages go on different platforms:
       Windows: debug output stream
       Android: log output
       Others: standard error output (stderr)

 @{
*/

//! The predefined log priorities
enum class log_priority : std::underlying_type_t<::SDL_LogPriority> {
    verbose = SDL_LOG_PRIORITY_VERBOSE,
    debug = SDL_LOG_PRIORITY_DEBUG,
    info = SDL_LOG_PRIORITY_INFO,
    warn = SDL_LOG_PRIORITY_WARN,
    error = SDL_LOG_PRIORITY_ERROR,
    critical = SDL_LOG_PRIORITY_CRITICAL
};

namespace detail {
    template <>
    struct c_type<log_priority> {
        using type = SDL_LogPriority;
    };

    template <>
    struct cpp_type<::SDL_LogPriority> {
        using type = sdl::log_priority;
    };
}

namespace log_category {

    /*! The predefined log categories

     By default the `application` category is enabled at the INFO level,
     the `assert` category is enabled at the WARN level, `test` is enabled
     at the VERBOSE level and all other categories are enabled at the
     CRITICAL level.
    */
    enum log_category : int {
        application = SDL_LOG_CATEGORY_APPLICATION,
        error = SDL_LOG_CATEGORY_ERROR,
        assert = SDL_LOG_CATEGORY_ASSERT,
        system = SDL_LOG_CATEGORY_SYSTEM,
        audio = SDL_LOG_CATEGORY_AUDIO,
        video = SDL_LOG_CATEGORY_VIDEO,
        render = SDL_LOG_CATEGORY_RENDER,
        input = SDL_LOG_CATEGORY_INPUT,
        test = SDL_LOG_CATEGORY_TEST,

        reserved1 = SDL_LOG_CATEGORY_RESERVED1,
        reserved2 = SDL_LOG_CATEGORY_RESERVED2,
        reserved3 = SDL_LOG_CATEGORY_RESERVED3,
        reserved4 = SDL_LOG_CATEGORY_RESERVED4,
        reserved5 = SDL_LOG_CATEGORY_RESERVED5,
        reserved6 = SDL_LOG_CATEGORY_RESERVED6,
        reserved7 = SDL_LOG_CATEGORY_RESERVED7,
        reserved8 = SDL_LOG_CATEGORY_RESERVED8,
        reserved9 = SDL_LOG_CATEGORY_RESERVED9,
        reserved10 = SDL_LOG_CATEGORY_RESERVED10,

        custom = SDL_LOG_CATEGORY_CUSTOM
    };

    //! Sets the priority of a particular log category
    inline void set_priority(int category, log_priority priority) {
        detail::c_call(::SDL_LogSetPriority, category, priority);
    }

    //! Gets the priority of a particular log category
    inline log_priority get_priority(int category) {
        return detail::c_call(::SDL_LogGetPriority, category);
    }

} // end namespace log_category

namespace detail {

    class logger {
    public:
        logger() = default;

        logger(const logger&) = delete;

        logger(logger&&) = default;

        ~logger();

        logger& operator<<(log_category::log_category);

        logger& operator<<(log_priority);

        template <typename T>
        logger& operator<<(T&&);

    private:
        string str;
        int category = log_category::application;
        log_priority priority = log_priority::info;
    };

    inline logger::~logger() {
        detail::c_call(::SDL_LogMessage, category, priority, "%s", str);
    }

    template <typename T>
    logger& logger::operator<<(T&& entry) {
        string_append(str, std::forward<T>(entry));

        return *this;
    }

    inline logger& logger::operator<<(log_category::log_category category) {
        this->category = category;
        return *this;
    }

    inline logger& logger::operator<<(log_priority priority) {
        this->priority = priority;
        return *this;
    }

} // end namespace detail

//! Return a logger object with can be used like a C++ ostream.
inline auto log() { return detail::logger{}; }

//! Log a message with category `log_category::application` and priority
//! `log_priority::info`
template <typename... T>
void log(const char* format, T&&... args) {
    detail::c_call(::SDL_Log, format, std::forward<T>(args)...);
}

//! Log a message with priority `log_priority::verbose`
template <typename... T>
void log_verbose(int category, const char* format, T&&... args) {
    detail::c_call(::SDL_LogVerbose, category, format,
                   std::forward<T>(args)...);
}

//! Log a message with priority `log_priority::debug`
template <typename... T>
void log_debug(int category, const char* format, T&&... args) {
    detail::c_call(::SDL_LogDebug, category, format, std::forward<T>(args)...);
}

//! Log a message with priority `log_priority::info`
template <typename... T>
void log_info(int category, const char* format, T&&... args) {
    detail::c_call(::SDL_LogInfo, category, format, std::forward<T>(args)...);
}

//! Log a message with priority `log_priority::warn`
template <typename... T>
void log_warn(int category, const char* format, T&&... args) {
    detail::c_call(::SDL_LogWarn, category, format, std::forward<T>(args)...);
}

//! Log a message with priority `log_priority::error`
template <typename... T>
void log_error(int category, const char* format, T&&... args) {
    detail::c_call(::SDL_LogError, category, format, std::forward<T>(args)...);
}

//! Log a message with priority `log_priority::critical`
template <typename... T>
void log_critical(int category, const char* format, T&&... args) {
    detail::c_call(::SDL_LogCritical, category, format,
                   std::forward<T>(args)...);
}

//! Log a message wih custom category and priority
template <typename... T>
void log_message(int category, log_priority priority, const char* format,
                 T&&... args) {
    detail::c_call(::SDL_LogMessage, category, priority, format,
                   std::forward<T>(args)...);
}

namespace detail {

    template <typename Func>
    struct log_output_cb {
        static void callback(void* data, int category,
                             ::SDL_LogPriority priority, const char* message) {
            auto self = static_cast<log_output_cb*>(data);
            return self->func(category, static_cast<log_priority>(priority),
                              message);
        }

        log_output_cb(Func func) : func(func) {
            // There doesn't seem to be any way to restore the default log
            // handler
            // in SDL (setting the log function to nullptr stops logging
            // completely)
            // so instead we save the old log function and restore it on
            // destruction.
            // This could lead to lifetime issues when multiple log output
            // callbacks
            // are used, so... don't do that?
            ::SDL_LogGetOutputFunction(&old_func, &old_user_data);
            ::SDL_LogSetOutputFunction(callback, this);
        }

        ~log_output_cb() {
            ::SDL_LogSetOutputFunction(old_func, old_user_data);
        }

        // Move-only
        log_output_cb(const log_output_cb&) = delete;

        log_output_cb& operator=(const log_output_cb&) = delete;

        log_output_cb(log_output_cb&&) = default;

        log_output_cb& operator=(log_output_cb&&) = default;

        Func func;
        ::SDL_LogOutputFunction old_func = nullptr;
        void* old_user_data = nullptr;
    };

} // end namespace detail

//! Set a new log output function.
//!
//! @param func A callable with signature
//!     `void(int category, log_priority priority, const char* message)`
//!
//! @returns A handle representing the callback. The lifetime of the callback
//!   funtion is tied to this value. When the return value goes out of scope,
//!   the previously set log output function will be reinstalled.
template <typename Func>
SDLXX_ATTR_WARN_UNUSED_RESULT auto log_set_output_function(Func func)
    -> detail::log_output_cb<Func> {
    return detail::log_output_cb<Func>(func);
}

} // end namespace sdl

#endif // SDLXX_LOG_HPP
