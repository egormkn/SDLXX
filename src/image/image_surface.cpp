#include "sdlxx/image/image_surface.h"

#include <SDL_image.h>

using namespace sdlxx;

ImageSurface::ImageSurface(const std::string& path) : Surface(IMG_Load(path.c_str())) {}
