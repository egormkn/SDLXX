# Range of supported CMake versions to pick up the best policies
cmake_minimum_required(VERSION 3.12...3.15)

# Project name and some basic information
project(SDLXX
    VERSION 1.0.0
    DESCRIPTION "Modern C++ wrapper for SDL"
    HOMEPAGE_URL "https://github.com/egormkn/SDLXX"
    LANGUAGES CXX)

# Set directory for helper modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/tools/cmake")

# Require out-of-source builds
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "You cannot build in a source directory")
endif()

# Determine if project is built as the main project or as a subproject
set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()

# If this is the main project and not included through add_subdirectory
if(MAIN_PROJECT)
    message(STATUS "Building ${PROJECT_NAME} with CMake v${CMAKE_VERSION}")

    # Optionally set things like CMAKE_CXX_STANDARD or
    # CMAKE_POSITION_INDEPENDENT_CODE here

    # Disable compiler extensions for better portability
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Improve support of folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Declare options that enable examples, docs, tests and static checks
    option(SDLXX_BUILD_EXAMPLES "Build examples" OFF)
    option(SDLXX_BUILD_DOCS "Build documentation" OFF)
    option(SDLXX_BUILD_TESTS "Build tests" OFF)
    option(SDLXX_ENABLE_CHECKS "Enable static analysis tools" OFF)

    # Enable static analysis tools
    if(SDLXX_ENABLE_CHECKS)
        include(StaticChecks)
    endif()
endif()

# Build library
add_subdirectory(src)

# Build documentation if this is the main project
if(MAIN_PROJECT AND SDLXX_BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# Build examples if this is the main project
if(MAIN_PROJECT AND SDLXX_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Build tests if this is the main project
if(MAIN_PROJECT AND SDLXX_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

