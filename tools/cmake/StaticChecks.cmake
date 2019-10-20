# Enable Clang-Tidy linter
find_program(CLANG_TIDY
    NAMES clang-tidy
    DOC "Path to the Clang-Tidy tool")
if(CLANG_TIDY)
    message(STATUS "Found Clang-Tidy: ${CLANG_TIDY}")
    set(CLANG_TIDY_CHECKS "*")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY};-config=;-header-filter=\"${CMAKE_SOURCE_DIR}/include/*\"")
else()
    message(STATUS "Clang-Tidy not found")
endif()

# Enable CppCheck linter
find_program(CPPCHECK
    NAMES cppcheck
    DOC "Path to the CppCheck tool")
if(CPPCHECK)
    message(STATUS "Found CppCheck: ${CPPCHECK}")
    set(CMAKE_CXX_CPPCHECK "${CPPCHECK}")
else()
    message(STATUS "CppCheck not found")
endif()

# Enable Cpplint linter
find_program(CPPLINT
    NAMES cpplint
    DOC "Path to the Cpplint tool")
if(CPPLINT)
    message(STATUS "Found Cpplint: ${CPPLINT}")
    set(CMAKE_CXX_CPPLINT "${CPPLINT}")
else()
    message(STATUS "Cpplint not found")
endif()

# Enable include-what-you-use linter
find_program(INCLUDE_WHAT_YOU_USE
    NAMES include-what-you-use iwyu
    DOC "Path to the include-what-you-use tool")
if(INCLUDE_WHAT_YOU_USE)
    message(STATUS "Found include-what-you-use: ${INCLUDE_WHAT_YOU_USE}")
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
else()
    message(STATUS "Include-what-you-use not found")
endif()

# Enable link-what-you-use feature
set(CMAKE_LINK_WHAT_YOU_USE TRUE)
