#include "sdlxx/image/image_texture.h"

#include <SDL_image.h>

using namespace sdlxx;

ImageTexture::ImageTexture(Renderer& renderer, const std::string& path)
    : Texture(IMG_LoadTexture(GetRendererPtr(renderer), path.c_str())) {}
