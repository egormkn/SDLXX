#include <SDL_image.h>
#include <sdlxx/image/Image.h>

using namespace sdlxx::image;

Image::Image(const std::string& file) : Surface(IMG_Load(file.c_str())) {
  if (!surface_ptr) {
    throw std::runtime_error("Failed to load image '" + file + "': " +
                             std::string(IMG_GetError()));
  }
}

/*
Texture::Texture(const std::string& path,
                 const std::shared_ptr<Renderer>& renderer, int w, int h) {
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    throw std::runtime_error("Unable to load image" +
                             std::string(IMG_GetError()));
  }
  SDL_SetColorKey(surface, SDL_TRUE,
                  SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

  // if (w > 0 && h > 0) {
  //     SDL_Rect stretchRect;
  //     stretchRect.x = 0;
  //     stretchRect.y = 0;
  //     stretchRect.w = w;
  //     stretchRect.h = h;
  //     SDL_Surface *scaled = SDL_CreateRGBSurface(0, w, h, 32, 0,0,0,0);
  //     SDL_BlitScaled(surface, NULL, scaled, &stretchRect);
  //     SDL_SetColorKey(scaled, SDL_TRUE, SDL_MapRGB(scaled->format, 0, 0xFF,
  // 0xFF)); SDL_FreeSurface(surface); surface = scaled;
  // }

  texture_ptr = SDL_CreateTextureFromSurface(
      static_cast<SDL_Renderer*>(renderer->renderer_ptr), surface);
  if (!texture_ptr) {
    throw std::runtime_error("Unable to create texture: " +
                             std::string(SDL_GetError()));
  }
  width = surface->w;
  height = surface->h;
  SDL_FreeSurface(surface);
}

Texture::Texture(const std::string& text, const Color& color,
                 const sdlxx::ttf::Font& font,
                 const std::shared_ptr<Renderer>& renderer) {
  Surface surface =
      font.render(text, sdlxx::ttf::Font::TTF_MODE_BLENDED, color);
  texture_ptr = SDL_CreateTextureFromSurface(
      static_cast<SDL_Renderer*>(renderer->renderer_ptr),
      static_cast<SDL_Surface*>(surface.surface_ptr));
  if (texture_ptr == nullptr) {
    throw std::runtime_error("Unable to create texture" +
                             std::string(SDL_GetError()));
  }
  Dimensions d = surface.GetSize();
  width = d.width;
  height = d.height;
}

void Texture::fill(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* dest,
                   double angle, SDL_Point* center, SDL_RendererFlip flip) {
  if (dest == nullptr) {
    SDL_RenderCopyEx(renderer, static_cast<SDL_Texture*>(texture_ptr), clip,
                     dest, angle, center, flip);
  } else {
    for (int x = dest->x; x < dest->x + dest->w; x += width) {
      for (int y = dest->y; y < dest->y + dest->h; y += height) {
        SDL_Rect d;
        d.x = x;
        d.y = y;
        d.w = width;
        d.h = height;
        render(renderer, clip, &d, angle, center, flip);
      }
    }
  }
}
*/
