
#include "catch.hpp"

#include <sdl++/log.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace {

struct log_entry {
    int category;
    SDL_LogPriority priority;
    std::string message;
};

inline bool operator==(const log_entry& lhs, const log_entry& rhs) {
    return std::tie(lhs.category, lhs.priority, lhs.message) ==
           std::tie(rhs.category, rhs.priority, rhs.message);
}

void test_log_func(void* user_data, int category, SDL_LogPriority priority,
                   const char* message) {
    auto* vec = static_cast<std::vector<log_entry>*>(user_data);
    vec->push_back(log_entry{category, priority, message});
}

// Test class with an overloaded operator<<
struct test_class {
    std::string msg;
};

std::ostream& operator<<(std::ostream& os, const test_class& t) {
    return os << t.msg;
}

} // end anonymous namespace

TEST_CASE("Setting log priority per category works correctly", "[log]") {
    sdl::log_category::set_priority(sdl::log_category::custom,
                                    sdl::log_priority::verbose);
    REQUIRE(SDL_LogGetPriority(SDL_LOG_CATEGORY_CUSTOM) ==
            SDL_LOG_PRIORITY_VERBOSE);

    SDL_LogResetPriorities();
}

TEST_CASE("Getting log priority per category works correctly", "[log]") {
    SDL_LogSetPriority(SDL_LOG_CATEGORY_CUSTOM + 1, SDL_LOG_PRIORITY_WARN);

    REQUIRE(sdl::log_category::get_priority(sdl::log_category::custom + 1) ==
            sdl::log_priority::warn);

    SDL_LogResetPriorities();
}

TEST_CASE("Basic logging works correctly", "[log]") {
    // Set up the internal logging for testing
    std::vector<log_entry> internal_log;

    SDL_LogOutputFunction old_func = nullptr;
    void* old_user_data = nullptr;
    SDL_LogGetOutputFunction(&old_func, &old_user_data);

    SDL_LogSetOutputFunction(test_log_func, &internal_log);

    SECTION("SDL_Log() is wrapped correctly") {
        sdl::log("%s %d", "test", 1);
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION,
                                                  SDL_LOG_PRIORITY_INFO,
                                                  "test 1"}));
    }

    SECTION("SDL_LogVerbose() is wrapped correctly") {
        sdl::log_verbose(sdl::log_category::test, "%s %d", "test", 2);
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST,
                                                  SDL_LOG_PRIORITY_VERBOSE,
                                                  "test 2"}));
    }

    SECTION("SDL_LogDebug() is wrapped correctly") {
        sdl::log_debug(sdl::log_category::test, "%s %d", "test", 3);
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST,
                                                  SDL_LOG_PRIORITY_DEBUG,
                                                  "test 3"}));
    }

    SECTION("SDL_LogInfo() is wrapped correctly") {
        sdl::log_info(sdl::log_category::test, "%s %d", "test", 4);
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST,
                                                  SDL_LOG_PRIORITY_INFO,
                                                  "test 4"}));
    }

    SECTION("SDL_LogWarn() is wrapped correctly") {
        sdl::log_warn(sdl::log_category::test, "%s %d", "test", 5);
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST,
                                                  SDL_LOG_PRIORITY_WARN,
                                                  "test 5"}));
    }

    SECTION("SDL_LogError() is wrapped correctly") {
        sdl::log_error(sdl::log_category::test, "%s %d", "test", 6);
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST,
                                                  SDL_LOG_PRIORITY_ERROR,
                                                  "test 6"}));
    }

    SECTION("SDL_LogCritical() is wrapped correctly") {
        sdl::log_critical(sdl::log_category::test, "%s %d", "test", 7);
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST,
                                                  SDL_LOG_PRIORITY_CRITICAL,
                                                  "test 7"}));
    }

    SECTION("SDL_LogMessage() is wrapped correctly") {
        sdl::log_message(sdl::log_category::test, sdl::log_priority::critical,
                         "%s %d", "test", 8);
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST,
                                                  SDL_LOG_PRIORITY_CRITICAL,
                                                  "test 8"}));
    }

    SDL_LogSetOutputFunction(old_func, old_user_data);
}

TEST_CASE("Logger class works correctly", "[log]") {
    std::vector<log_entry> internal_log;

    SDL_LogOutputFunction old_func = nullptr;
    void* old_user_data = nullptr;
    SDL_LogGetOutputFunction(&old_func, &old_user_data);

    SDL_LogSetOutputFunction(test_log_func, &internal_log);

    SECTION("Logger can be created") {
        sdl::log() << "test " << 1;
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION,
                                                  SDL_LOG_PRIORITY_INFO,
                                                  "test 1"}));
    }

    SECTION("Logger can use custom classes") {
        sdl::log() << test_class{"test 2"};
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION,
                                                  SDL_LOG_PRIORITY_INFO,
                                                  "test 2"}));
    }

    SECTION("Logger can use custom categories") {
        sdl::log() << "test 3" << sdl::log_category::test;
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_TEST,
                                                  SDL_LOG_PRIORITY_INFO,
                                                  "test 3"}));
    }

    SECTION("Logger can use custom priorities") {
        sdl::log() << sdl::log_priority::critical << "test " << 4;
        REQUIRE((internal_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION,
                                                  SDL_LOG_PRIORITY_CRITICAL,
                                                  "test 4"}));
    }

    SDL_LogSetOutputFunction(old_func, old_user_data);
}

TEST_CASE("Custom log functions work correctly", "[log]") {

    std::vector<log_entry> test_log;

    auto handle = sdl::log_set_output_function(
        [&test_log](int cat, sdl::log_priority prio, const char* msg) {
            // std::cout << msg << std::endl;
            test_log.push_back(
                log_entry{cat, static_cast<SDL_LogPriority>(prio), msg});
        });

    sdl::log() << test_class{"test 1"};
    REQUIRE((test_log.back() == log_entry{SDL_LOG_CATEGORY_APPLICATION,
                                          SDL_LOG_PRIORITY_INFO, "test 1"}));
}
