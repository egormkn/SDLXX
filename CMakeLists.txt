# Works with 3.12 and tested through 3.15
cmake_minimum_required(VERSION 3.12...3.15)

# Project name and a few useful settings
project(SDLXX VERSION 1.0.0
              DESCRIPTION "Modern C++17 wrapper for SDL"
              HOMEPAGE_URL "https://github.com/egormkn/SDLXX"
              LANGUAGES CXX)

# Require out-of-source builds
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "You cannot build in a source directory.")
endif()

# Use cmake folder for helper modules (Find*.cmake)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Determine if project is built as the main project or as a subproject
set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
    message(STATUS "Main project: ${CMAKE_PROJECT_NAME}")
    message(STATUS "CMake version: ${CMAKE_VERSION}")
endif()

# If this is the main project and not included through add_subdirectory
if(MAIN_PROJECT)

    # Optionally set things like CMAKE_CXX_STANDARD or
    # CMAKE_POSITION_INDEPENDENT_CODE here

    # Disable compiler extensions for better compatibility
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Improve support of folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Enable testing if this is the main project
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    if(BUILD_TESTING)
        include(CTest)
    endif()

    # Enable documentation if this is the main project
    find_package(Doxygen)
    if(Doxygen_FOUND)
        include(cmake/Doxygen.cmake)
    else()
	    message(STATUS "Doxygen not found, not building docs")
    endif()

    option(ENABLE_LINTING "Enable code analysis tools" OFF)

    if(ENABLE_LINTING)
        # Enable clang-tidy linter if this is the main project
        find_program(CLANG_TIDY
            NAMES clang-tidy
            DOC "Path to the clang-tidy tool")
        if(CLANG_TIDY)
            message(STATUS "Found clang-tidy: ${CLANG_TIDY}")
            set(CLANG_TIDY_CHECKS "*")
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY};-config=;-header-filter=\"${CMAKE_SOURCE_DIR}/include/*\"")
        else()
            message(STATUS "Clang-tidy not found, skipping checks")
        endif()

        # Enable include-what-you-use linter if this is the main project
        find_program(INCLUDE_WHAT_YOU_USE
            NAMES include-what-you-use iwyu
            DOC "Path to the include-what-you-use tool")
        if(INCLUDE_WHAT_YOU_USE)
            message(STATUS "Found include-what-you-use: ${INCLUDE_WHAT_YOU_USE}")
            set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
            set(CMAKE_C_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
        else()
            message(STATUS "Include-what-you-use not found, skipping checks")
        endif()
    endif()
endif()

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(app)

# Testing only available if this is the main project
if(MAIN_PROJECT AND BUILD_TESTING)
    add_subdirectory(test)
endif()

