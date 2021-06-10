#include "sdlxx/core/surface.h"

#include <SDL_surface.h>

#include "sdlxx/core/color.h"

using namespace sdlxx;

Surface::Surface(int width, int height, int depth, uint32_t r_mask, uint32_t g_mask, uint32_t b_mask,
                 uint32_t a_mask)
    : Surface(SDL_CreateRGBSurface(0, width, height, depth, r_mask, g_mask, b_mask, a_mask)) {}

Surface::Surface(int width, int height, int depth, uint32_t format)
    : Surface(SDL_CreateRGBSurfaceWithFormat(0, width, height, depth, format)) {}

Surface::Surface(void* pixels, int width, int height, int depth, int pitch, uint32_t r_mask,
                 uint32_t g_mask, uint32_t b_mask, uint32_t a_mask)
    : Surface(SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, r_mask, g_mask, b_mask,
                                       a_mask)) {}

Surface::Surface(void* pixels, int width, int height, int depth, int pitch, uint32_t format)
    : Surface(SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, format)) {}

Surface::Surface(SDL_Surface* ptr) : surface_ptr(ptr) {
  if (!surface_ptr) {
    throw SurfaceException("Failed to allocate a surface");
  }
}

Surface::Surface(const Surface& other) : Surface(SDL_DuplicateSurface(other.surface_ptr.get())) {}

Surface& Surface::operator=(const Surface& other) {
  if (this != &other) {
    Surface temp(other);
    std::swap(temp.surface_ptr, surface_ptr);
  }
  return *this;
}

bool Surface::Lock() { return SDL_LockSurface(surface_ptr.get()) == 0; }

void Surface::Unlock() { SDL_UnlockSurface(surface_ptr.get()); }

Surface Surface::LoadBMP(const std::string& file) {
  SDL_Surface* ptr = SDL_LoadBMP(file.c_str());
  return Surface(ptr);
}

void Surface::SaveBMP(const std::string& file) const {
  int return_code = SDL_SaveBMP(surface_ptr.get(), file.c_str());
  if (return_code != 0) {
    throw SurfaceException("Failed to save surface to " + file);
  }
}

void Surface::SetColorKey(Color color) {
  Uint32 key = SDL_MapRGB(surface_ptr->format, color.r, color.g, color.b);
  int return_code = SDL_SetColorKey(surface_ptr.get(), 1, key);
  if (return_code != 0) {
    throw SurfaceException("Failed to set color key for the surface");
  }
}

void Surface::ResetColorKey() {
  Uint32 key = SDL_MapRGB(surface_ptr->format, 0, 0, 0);
  int return_code = SDL_SetColorKey(surface_ptr.get(), 0, key);
  if (return_code != 0) {
    throw SurfaceException("Failed to reset color key for the surface");
  }
}

bool Surface::HasColorKey() const {
  return SDL_HasColorKey(surface_ptr.get()) == SDL_TRUE;
}

bool Surface::SetClipRectangle(const Rectangle& rectangle) {
  SDL_Rect rect{rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  return SDL_SetClipRect(surface_ptr.get(), &rect) == SDL_TRUE;
}

void Surface::DisableClipRectangle() { SDL_SetClipRect(surface_ptr.get(), NULL); }

Rectangle Surface::GetClipRectangle() const {
  SDL_Rect rect;
  SDL_GetClipRect(surface_ptr.get(), &rect);
  return {rect.x, rect.y, rect.w, rect.h};
}

std::optional<Surface> Surface::Convert(const SDL_PixelFormat* fmt, uint32_t flags) {
  SDL_Surface* result = SDL_ConvertSurface(surface_ptr.get(), fmt, flags);
  if (result) {
    return Surface(result);
  } else {
    return std::nullopt;
  }
}

std::optional<Surface> Surface::ConvertFormat(uint32_t pixel_format, uint32_t flags) {
  SDL_Surface* result = SDL_ConvertSurfaceFormat(surface_ptr.get(), pixel_format, flags);
  if (result) {
    return Surface(result);
  } else {
    return std::nullopt;
  }
}

void Surface::ConvertPixels(int width, int height, uint32_t src_format, const void* src,
                            int src_pitch, uint32_t dst_format, void* dst, int dst_pitch) {
  int return_code =
      SDL_ConvertPixels(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
  if (return_code != 0) {
    throw SurfaceException("Failed to convert pixels");
  }
}

void Surface::Fill(const Color& color) {
  uint32_t rgb_color = SDL_MapRGB(surface_ptr->format, color.r, color.g, color.b);
  int return_code = SDL_FillRect(surface_ptr.get(), nullptr, rgb_color);
  if (return_code != 0) {
    throw SurfaceException("Failed to fill a surface with color");
  }
}

void Surface::FillRectangle(const Rectangle& rectangle, const Color& color) {
  uint32_t rgb_color = SDL_MapRGB(surface_ptr->format, color.r, color.g, color.b);
  SDL_Rect rect{rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  int return_code = SDL_FillRect(surface_ptr.get(), &rect, rgb_color);
  if (return_code != 0) {
    throw SurfaceException("Failed to fill a surface rectangle with color");
  }
}

void Surface::FillRectangles(const std::vector<Rectangle>& rectangles, const Color& color) {
  uint32_t rgb_color = SDL_MapRGB(surface_ptr->format, color.r, color.g, color.b);
  std::vector<SDL_Rect> rects;
  rects.reserve(rectangles.size());
  for (const Rectangle& rectangle : rectangles) {
    rects.push_back({rectangle.x, rectangle.y, rectangle.width, rectangle.height});
  }
  int return_code = SDL_FillRects(surface_ptr.get(), rects.data(), rects.size(), rgb_color);
  if (return_code != 0) {
    throw SurfaceException("Failed to fill a surface rectangles with color");
  }
}

void Surface::Blit(const Surface& source) {
  int return_code = SDL_BlitSurface(source.surface_ptr.get(), NULL, surface_ptr.get(), NULL);
  if (return_code != 0) {
    throw SurfaceException("Failed to perform a blit of a surface");
  }
}

void Surface::Blit(const Surface& source, const Rectangle& source_rect,
                   const Rectangle& dest_rect) {
  SDL_Rect srcrect{source_rect.x, source_rect.y, source_rect.width, source_rect.height};
  SDL_Rect dstrect{dest_rect.x, dest_rect.y, dest_rect.width, dest_rect.height};
  int return_code =
      SDL_BlitSurface(source.surface_ptr.get(), &srcrect, surface_ptr.get(), &dstrect);
  if (return_code != 0) {
    throw SurfaceException("Failed to perform a blit of a surface");
  }
}

void Surface::BlitScaled(const Surface& source) {
  int return_code = SDL_BlitScaled(source.surface_ptr.get(), NULL, surface_ptr.get(), NULL);
  if (return_code == -1) {
    throw SurfaceException("Failed to perform scaled blit of a surface");
  }
}

void Surface::BlitScaled(const Surface& source, const Rectangle& source_rect,
                         const Rectangle& dest_rect) {
  SDL_Rect srcrect{source_rect.x, source_rect.y, source_rect.width, source_rect.height};
  SDL_Rect dstrect{dest_rect.x, dest_rect.y, dest_rect.width, dest_rect.height};
  int return_code = SDL_BlitScaled(source.surface_ptr.get(), &srcrect, surface_ptr.get(), &dstrect);
  if (return_code == -1) {
    throw SurfaceException("Failed to perform scaled blit of a surface");
  }
}

Dimensions Surface::GetSize() const { return {surface_ptr->w, surface_ptr->h}; }

void* Surface::GetPixels() const { return surface_ptr->pixels; }

SDL_PixelFormat* Surface::GetFormat() const { return surface_ptr->format; }

SDL_Surface* Surface::Release() { return surface_ptr.release(); }

void Surface::Deleter::operator()(SDL_Surface* ptr) const {
  if (ptr && (ptr->flags & SDL_DONTFREE) == 0) {
    SDL_FreeSurface(ptr);
  }
}

SurfaceLock::SurfaceLock(Surface& surface) : surface(surface) { surface.Lock(); }

SurfaceLock::~SurfaceLock() { surface.Unlock(); }
