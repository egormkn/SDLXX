# Works with 3.12 and tested through 3.15
cmake_minimum_required(VERSION 3.12...3.15)

# Project name and a few useful settings
project(SDLXX VERSION 1.0.0
              DESCRIPTION "Modern C++ binding for SDL"
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
    include(CTest)

    # Enable documentation if this is the main project
    find_package(Doxygen)
    if(Doxygen_FOUND)
	    add_subdirectory(docs)
    else()
	    message(STATUS "Doxygen not found, not building docs")
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

