# Add SDLXX library core and additional modules
add_subdirectory(core)
add_subdirectory(gui)
add_subdirectory(image)
add_subdirectory(mixer)
add_subdirectory(net)
add_subdirectory(ttf)

# Add TMX library (TODO: Move to a separate project)
add_subdirectory(tmx)
