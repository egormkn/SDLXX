#include "sdlxx/core/texture.h"

#include <SDL_render.h>

using namespace sdlxx::core;

using Format = Texture::Format;
using Access = Texture::Access;

Texture::Texture(Renderer& renderer, Dimensions dimensions, Texture::Format format,
                 Texture::Access access)
    : Texture(SDL_CreateTexture(GetRendererPtr(renderer), static_cast<Uint32>(format),
                                static_cast<int>(access), dimensions.width, dimensions.height)) {}

Texture::Texture(Renderer& renderer, const Surface& surface)
    : texture_ptr(
          SDL_CreateTextureFromSurface(GetRendererPtr(renderer), surface.surface_ptr.get())) {}

Texture::Texture(SDL_Texture* ptr) : texture_ptr(ptr) {
  if (!texture_ptr) {
    throw TextureException("Failed to create a texture");
  }
}

Texture::Attributes Texture::Query() const {
  Attributes attributes;
  int return_code = SDL_QueryTexture(texture_ptr.get(), &attributes.format,
                                     reinterpret_cast<int*>(&attributes.access),
                                     &attributes.dimensions.width, &attributes.dimensions.height);
  if (return_code != 0) {
    throw TextureException("Failed to query a texture");
  }
  return attributes;
}

void Texture::Deleter::operator()(SDL_Texture* ptr) const {
  if (ptr) {
    SDL_DestroyTexture(ptr);
  }
}

SDL_Renderer* Texture::GetRendererPtr(Renderer& renderer) { return renderer.renderer_ptr.get(); }

// Texture::Texture(std::shared_ptr<Renderer> renderer, int width, int height,
//                  Format format, Access access) {
//   texture_ptr =
//       SDL_CreateTexture(static_cast<SDL_Renderer*>(renderer->renderer_ptr),
//                         format, static_cast<int>(access), width, height);
//   if (!texture_ptr) {
//     throw std::runtime_error("Failed to create texture: " +
//                              std::string(SDL_GetError()));
//   }
// }
//
// Texture::Texture(std::shared_ptr<Renderer> renderer, const Surface& surface) {
////  texture_ptr = SDL_CreateTextureFromSurface(
////      static_cast<SDL_Renderer*>(renderer->renderer_ptr),
////      static_cast<SDL_Surface*>(surface.surface_ptr));
////  if (!texture_ptr) {
////    throw std::runtime_error("Failed to create texture from surface: " +
////                             std::string(SDL_GetError()));
////  }
//}
//
// Texture::~Texture() {
//  if (texture_ptr) {
//    SDL_DestroyTexture(static_cast<SDL_Texture*>(texture_ptr));
//    texture_ptr = nullptr;
//  }
//}
//
// std::tuple<Dimensions, Format, Access> Texture::query() const {
//  Uint32 format;
//  int access, width, height;
//  int return_code = SDL_QueryTexture(static_cast<SDL_Texture*>(texture_ptr),
//                                     &format, &access, &width, &height);
//  if (return_code != 0) {
//    throw std::runtime_error("Failed to Get texture data: " +
//                             std::string(SDL_GetError()));
//  }
//  Dimensions dimensions(width, height);
//  return {dimensions, format, static_cast<Access>(access)};
//}
//
// Dimensions Texture::getDimensions() const { return std::get<0>(query()); }
//
// uint32_t Texture::getFormat() const { return std::get<1>(query()); }
//
// Access Texture::getAccess() const { return std::get<2>(query()); }
//
// void Texture::setModulation(const Color& color) {
//  if (color.r != 0 && color.g != 0 && color.b != 0) {
//    int return_code = SDL_SetTextureColorMod(
//        static_cast<SDL_Texture*>(texture_ptr), color.r, color.g, color.b);
//    if (return_code != 0) {
//      throw std::runtime_error("Failed to set texture color modulation: " +
//                               std::string(SDL_GetError()));
//    }
//  }
//  if (color.a != 0) {
//    int return_code =
//        SDL_SetTextureAlphaMod(static_cast<SDL_Texture*>(texture_ptr), color.a);
//    if (return_code != 0) {
//      throw std::runtime_error("Failed to set texture alpha modulation: " +
//                               std::string(SDL_GetError()));
//    }
//  }
//}
//
// Color Texture::getModulation() const {
//  Uint8 r, g, b, a;
//  {
//    int return_code = SDL_GetTextureColorMod(
//        static_cast<SDL_Texture*>(texture_ptr), &r, &g, &b);
//    if (return_code != 0) {
//      throw std::runtime_error("Failed to Get texture color modulation: " +
//                               std::string(SDL_GetError()));
//    }
//  }
//  {
//    int return_code =
//        SDL_GetTextureAlphaMod(static_cast<SDL_Texture*>(texture_ptr), &a);
//    if (return_code != 0) {
//      throw std::runtime_error("Failed to Get texture alpha modulation: " +
//                               std::string(SDL_GetError()));
//    }
//  }
//  return {r, g, b, a};
//}

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
