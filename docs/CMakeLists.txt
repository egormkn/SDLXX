find_package(Doxygen)

if(DOXYGEN_FOUND)
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

  # FIXME: Exclude TMX from docs
  set(DOXYGEN_EXCLUDE_PATTERNS "${PROJECT_SOURCE_DIR}/include/tmx/*")

  # Add target for building documentation
  doxygen_add_docs(sdlxx_docs
          "${PROJECT_SOURCE_DIR}/README.md"
          "${PROJECT_SOURCE_DIR}/include"
          # ALL
          WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
          COMMENT "Documentation for ${PROJECT_NAME}"
          )
else()
  message(STATUS "Doxygen not found, not building documentation")
endif()

