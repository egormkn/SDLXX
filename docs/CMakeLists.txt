# Include undocumented public and protected methods and class members
set(DOXYGEN_EXTRACT_ALL YES)

# Improve STL support for documentation
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

# Add target for building documentation
doxygen_add_docs(docs
    "${PROJECT_SOURCE_DIR}/include"
    ALL
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
)
