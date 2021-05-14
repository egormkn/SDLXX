# Use STL debug mode
option(ENABLE_STL_DEBUG_MODE "Enable STL debug mode" OFF)

if(ENABLE_STL_DEBUG_MODE)
  message(STATUS "Enabling STL debug mode")
  add_compile_definitions(_GLIBCXX_DEBUG _GLIBCXX_DEBUG_PEDANTIC _LIBCPP_DEBUG=1)
endif()

# Use address sanitizer
option(ENABLE_ADDRESS_SANITIZER "Enable address sanitizer" OFF)

if(ENABLE_ADDRESS_SANITIZER)
  add_compile_options(-fsanitize=address -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls)
  link_libraries(-fsanitize=address)

  message(STATUS "Looking for llvm-symbolizer")
  find_program(LLVM_SYMBOLIZER
               NAMES llvm-symbolizer
               DOC "Path to the llvm-symbolizer tool")
  if(LLVM_SYMBOLIZER)
    message(STATUS "Looking for llvm-symbolizer - found (${LLVM_SYMBOLIZER})")
    message("Run an executable with\n"
            "ASAN_SYMBOLIZER_PATH=${LLVM_SYMBOLIZER} ASAN_OPTIONS=symbolize=1")
  else()
    message(STATUS "Looking for llvm-symbolizer - not found")
  endif()
endif()


# Use undefined behaviour sanitizer
option(ENABLE_UB_SANITIZER "Enable undefined behaviour sanitizer" OFF)

if(ENABLE_UB_SANITIZER)
  add_compile_options(-fsanitize=undefined -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls)
  link_libraries(-fsanitize=undefined)

  message(STATUS "Looking for llvm-symbolizer")
  find_program(LLVM_SYMBOLIZER
               NAMES llvm-symbolizer
               DOC "Path to the llvm-symbolizer tool")
  if(LLVM_SYMBOLIZER)
    message(STATUS "Looking for llvm-symbolizer - found (${LLVM_SYMBOLIZER})")
    message("Run an executable with\n"
            "UBSAN_SYMBOLIZER_PATH=${LLVM_SYMBOLIZER} UBSAN_OPTIONS=symbolize=1")
  else()
    message(STATUS "Looking for llvm-symbolizer - not found")
  endif()
endif()
