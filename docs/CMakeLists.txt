find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
  message(STATUS "Doxygen not found, not building documentation")
  return()
endif()

# TODO: Move variables to Doxyfile
# TODO: Use doxygen-bootstrapped theme

# Include undocumented public and protected methods and class members
set(DOXYGEN_EXTRACT_ALL YES)

# Improve STL support
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

# Hide include guards from the documentation
set(DOXYGEN_EXCLUDE_SYMBOLS "SDLXX_*_H" "SDLXX_*_HPP")

# Set repository README as the main mage
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")

# Set directory with the image files
set(DOXYGEN_IMAGE_PATH "${PROJECT_SOURCE_DIR}/data")

set(DOXYGEN_TAGFILES "${PROJECT_SOURCE_DIR}/docs/SDL.tag")

set(DOXYGEN_ALIASES [[upstream=\xrefitem upstream \"Use instead of\" \"Implemented SDL functions\" \ref]])

# Add target for building documentation
doxygen_add_docs(SDLXX_docs
                 "${PROJECT_SOURCE_DIR}/README.md"
                 "${PROJECT_SOURCE_DIR}/include"
                 # ALL
                 WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
                 COMMENT "Documentation for ${PROJECT_NAME}")

# configure_file(Doxyfile.in Doxyfile @ONLY)

# add_custom_target(doc
#                   ${DOXYGEN_EXECUTABLE} Doxyfile
#                   comment "Generating Doxygen documentation" verbatim)
