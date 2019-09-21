# Works with 3.12 and tested through 3.15
cmake_minimum_required(VERSION 3.12...3.15)

# Project name and a few useful settings
project(SDLXX VERSION 1.0.0
              DESCRIPTION "Modern C++ binding for SDL"
              HOMEPAGE_URL "https://github.com/egormkn/SDLXX"
              LANGUAGES CXX)

# If this is the main project, and not included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Disable compiler extensions for better compatibility
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Improve support of folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Enable testing if this is the main project
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

# Testing only available if this is the main project
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
