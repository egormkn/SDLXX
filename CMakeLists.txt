# Range of supported CMake versions to pick up the best policies
cmake_minimum_required(VERSION 3.12...3.20)

# Require out-of-source builds
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR
          "You cannot build in a source directory.\n"
          "Please use `cmake -H . -B build`.\n"
          "NOTE: cmake will now create CMakeCache.txt and CMakeFiles/*.\n"
          "      You must delete them, or cmake will refuse to work.")
endif()

# Project name and some basic information
project(SDLXX
        VERSION 1.0.0
        DESCRIPTION "Modern C++ wrapper for SDL"
        HOMEPAGE_URL "https://github.com/egormkn/SDLXX"
        LANGUAGES CXX)

# Set directory for helper modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Determine if project is built as the top-level project or as a subproject
if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
  set(MAIN_PROJECT ON)
else()
  set(MAIN_PROJECT OFF)
endif()

# If this is the top-level project and not included through add_subdirectory
if(MAIN_PROJECT)
  message(STATUS
          "Building ${PROJECT_NAME} with CMake v${CMAKE_VERSION} "
          "using ${CMAKE_CXX_COMPILER_ID} v${CMAKE_CXX_COMPILER_VERSION}")

  # Set C++ standard
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  # Disable compiler extensions (-std=c++xx instead of -std=g++xx)
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Improve support of folders in some IDE's
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # TODO: Remove
  add_compile_options(-w -Wno-error=shadow -Wno-error=reorder)

  # Declare options that enable documentation, examples and tests
  option(BUILD_DOCS "Build documentation" OFF)
  option(BUILD_EXAMPLES "Build examples" OFF)
  option(BUILD_TESTING "Build tests" OFF)

  # Enable static and dynamic checks
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # set(ENABLE_WARNINGS ON)
    # set(ENABLE_CLANG_TIDY ON)
    # set(ENABLE_CPPCHECK ON)
    # set(ENABLE_CPPLINT ON)
    # set(ENABLE_IWYU ON)
    # set(ENABLE_LWYU ON)
    # set(ENABLE_STL_DEBUG_MODE ON)
    # set(ENABLE_ADDRESS_SANITIZER ON)
    # set(ENABLE_UB_SANITIZER ON)
  endif()

  include(StaticChecks)
  include(DynamicChecks)
endif()

# Build sources
add_subdirectory(src)

# Build documentation if this is the main project
if(MAIN_PROJECT AND BUILD_DOCS)
  add_subdirectory(docs)
endif()

# Build examples if this is the main project
if(MAIN_PROJECT AND BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# Build tests if this is the main project
if(MAIN_PROJECT AND BUILD_TESTING)
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif()
