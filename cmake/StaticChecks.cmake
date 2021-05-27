# Use compiler warnings
option(ENABLE_COMPILER_WARNINGS "Enable recommended compiler warnings" OFF)

if(ENABLE_COMPILER_WARNINGS)
  if(MSVC)
    # Warning level 4, all warnings as errors, strict standard conformance
    add_compile_options(/W4 /WX /permissive-)
  else()
    # Lots of warnings, all warnings as errors, strict standard conformance, optimization
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Werror -pedantic
                        -Wno-unused-variable -Wno-unused-parameter -O3)
  endif()
endif()

# Use clang-tidy tool
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)

if(ENABLE_CLANG_TIDY)
  message(STATUS "Looking for clang-tidy")
  find_program(CLANG_TIDY
               NAMES clang-tidy
               DOC "Path to the clang-tidy tool")
  if(CLANG_TIDY)
    message(STATUS "Looking for clang-tidy - found (${CLANG_TIDY})")
    set(CLANG_TIDY_CHECKS "*")
    set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY};-config=;-header-filter=\"${CMAKE_SOURCE_DIR}/include/*\"")
  else()
    message(STATUS "Looking for clang-tidy - not found")
  endif()
endif()

# Use cppcheck tool
option(ENABLE_CPPCHECK "Enable cppcheck" OFF)

if(ENABLE_CPPCHECK)
  message(STATUS "Looking for cppcheck")
  find_program(CPPCHECK
               NAMES cppcheck
               DOC "Path to the cppcheck tool")
  if(CPPCHECK)
    message(STATUS "Looking for cppcheck - found (${CPPCHECK})")
    set(CMAKE_CXX_CPPCHECK "${CPPCHECK}")
  else()
    message(STATUS "Looking for cppcheck - not found")
  endif()
endif()

# Use cpplint tool
option(ENABLE_CPPLINT "Enable cpplint" OFF)

if(ENABLE_CPPLINT)
  message(STATUS "Looking for cpplint")
  find_program(CPPLINT
               NAMES cpplint
               DOC "Path to the cpplint tool")
  if(CPPLINT)
    message(STATUS "Looking for cpplint - found (${CPPLINT})")
    set(CMAKE_CXX_CPPLINT "${CPPLINT}")
  else()
    message(STATUS "Looking for cpplint - not found")
  endif()
endif()

# Use include-what-you-use tool
option(ENABLE_IWYU "Enable include-what-you-use" OFF)

if(ENABLE_IWYU)
  message(STATUS "Looking for include-what-you-use")
  find_program(IWYU
               NAMES include-what-you-use iwyu
               DOC "Path to the include-what-you-use tool")
  if(IWYU)
    message(STATUS "Looking for include-what-you-use - found (${IWYU})")
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU})
  else()
    message(STATUS "Looking for include-what-you-use - not found")
  endif()
endif()

# Use link-what-you-use cmake feature
option(ENABLE_LWYU "Enable link-what-you-use feature" OFF)

if(ENABLE_LWYU)
  set(CMAKE_LINK_WHAT_YOU_USE ON)
endif()
