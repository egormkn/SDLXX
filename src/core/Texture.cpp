#include <stdexcept>

#include <sdlxx/core/Texture.h>

using namespace sdlxx::core;

Texture::Texture(void* texture_ptr) : texture_ptr(texture_ptr) {
  SDL_QueryTexture(static_cast<SDL_Texture*>(texture_ptr), &format, &access,
                   &width, &height);
}

Texture::Texture(const std::string& path, const std::shared_ptr<Renderer>& renderer, int w,
                 int h) {
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    throw std::runtime_error("Unable to load image" +
                             std::string(IMG_GetError()));
  }
  SDL_SetColorKey(surface, SDL_TRUE,
                  SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

  /*if (w > 0 && h > 0) {
      SDL_Rect stretchRect;
      stretchRect.x = 0;
      stretchRect.y = 0;
      stretchRect.w = w;
      stretchRect.h = h;
      SDL_Surface *scaled = SDL_CreateRGBSurface(0, w, h, 32, 0,0,0,0);
      SDL_BlitScaled(surface, NULL, scaled, &stretchRect);
      SDL_SetColorKey(scaled, SDL_TRUE, SDL_MapRGB(scaled->format, 0, 0xFF,
  0xFF)); SDL_FreeSurface(surface); surface = scaled;
  }*/

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
                 const sdlxx::ttf::Font& font, const std::shared_ptr<Renderer>& renderer) {
  Surface surface = font.render(text, sdlxx::ttf::Font::TTF_MODE_BLENDED, color);
  texture_ptr = SDL_CreateTextureFromSurface(
      static_cast<SDL_Renderer*>(renderer->renderer_ptr),
      static_cast<SDL_Surface*>(surface.surface_ptr));
  if (texture_ptr == nullptr) {
    throw std::runtime_error("Unable to create texture" +
                             std::string(SDL_GetError()));
  }
  Dimensions d = surface.getSize();
  width = d.width;
  height = d.height;
}

Texture::~Texture() {
  width = 0;
  height = 0;
  access = SDL_TEXTUREACCESS_STATIC;
  format = SDL_PIXELFORMAT_UNKNOWN;
  if (texture_ptr != nullptr) {
    SDL_DestroyTexture(static_cast<SDL_Texture*>(texture_ptr));
    texture_ptr = nullptr;
  }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  SDL_SetTextureColorMod(static_cast<SDL_Texture*>(texture_ptr), red, green,
                         blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(static_cast<SDL_Texture*>(texture_ptr), blending);
}

void Texture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(static_cast<SDL_Texture*>(texture_ptr), alpha);
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* dest,
                     double angle, SDL_Point* center, SDL_RendererFlip flip) {
  // Set rendering space and render to screen

  // Render to screen
  SDL_RenderCopyEx(renderer, static_cast<SDL_Texture*>(texture_ptr), clip, dest,
                   angle, center, flip);
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

int Texture::getWidth() const { return width; }

int Texture::getHeight() const { return height; }

SDL_Texture* Texture::getSDLTexture() const {
  return static_cast<SDL_Texture*>(texture_ptr);
}
