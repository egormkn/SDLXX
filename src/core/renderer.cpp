#include "sdlxx/core/renderer.h"

#include <cmath>
#include <cstddef>

#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>

#include "sdlxx/core/point.h"
#include "sdlxx/core/rectangle.h"
#include "sdlxx/core/renderable.h"
#include "sdlxx/core/surface.h"
#include "sdlxx/core/texture.h"
#include "sdlxx/core/window.h"

using namespace sdlxx;

Renderer::Driver::Driver(int index) : index(index) {}

std::string Renderer::Driver::GetName() const {
  SDL_RendererInfo info;
  int return_code = SDL_GetRenderDriverInfo(index, &info);
  if (return_code != 0) {
    throw RendererException("Failed to get a name for a driver " + std::to_string(index));
  }
  return info.name;
}

BitMask<Renderer::Flag> Renderer::Driver::GetFlags() const {
  SDL_RendererInfo info;
  int return_code = SDL_GetRenderDriverInfo(index, &info);
  if (return_code != 0) {
    throw RendererException("Failed to get flags for a driver " + std::to_string(index));
  }
  return BitMask<Flag>{info.flags};
}

std::vector<uint32_t> Renderer::Driver::GetTextureFormats() const {
  SDL_RendererInfo info;
  int return_code = SDL_GetRenderDriverInfo(index, &info);
  if (return_code != 0) {
    throw RendererException("Failed to get texture formats for a driver " + std::to_string(index));
  }
  Uint32* data = info.texture_formats;
  Uint32 size = info.num_texture_formats;
  return std::vector<uint32_t>(data, data + size);
}

Dimensions Renderer::Driver::GetMaximumTextureSize() const {
  SDL_RendererInfo info;
  int return_code = SDL_GetRenderDriverInfo(index, &info);
  if (return_code != 0) {
    throw RendererException("Failed to get texture size for a driver " + std::to_string(index));
  }
  return {info.max_texture_width, info.max_texture_height};
}

int Renderer::Driver::GetIndex() const { return index; }

std::vector<Renderer::Driver> Renderer::GetDrivers() {
  int num_drivers = SDL_GetNumRenderDrivers();
  std::vector<Driver> result;
  result.reserve(num_drivers);
  for (int i = 0; i < num_drivers; ++i) {
    result.emplace_back(i);
  }
  return result;
}

Renderer::Renderer(Window& window, BitMask<Flag> flags)
    : renderer_ptr(
          SDL_CreateRenderer(window.window_ptr.get(), -1, static_cast<Uint32>(flags.value))) {
  if (renderer_ptr == nullptr) {
    throw RendererException("Failed to create a 2D rendering context for a window");
  }
}

Renderer::Renderer(Window& window, Renderer::Driver driver, BitMask<Flag> flags)
    : renderer_ptr(SDL_CreateRenderer(window.window_ptr.get(), driver.GetIndex(),
                                      static_cast<Uint32>(flags.value))) {
  if (renderer_ptr == nullptr) {
    throw RendererException("Failed to create a 2D rendering context for a window");
  }
}

Renderer::Renderer(Surface& surface)
    : renderer_ptr(SDL_CreateSoftwareRenderer(surface.surface_ptr.get())) {
  if (renderer_ptr == nullptr) {
    throw RendererException("Failed to create a 2D rendering context for a surface");
  }
}

Dimensions Renderer::GetOutputSize() const {
  Dimensions dimensions;
  int return_code =
      SDL_GetRendererOutputSize(renderer_ptr.get(), &dimensions.width, &dimensions.height);
  if (return_code != 0) {
    throw RendererException("Failed to get output size for the renderer");
  }
  return dimensions;
}

bool Renderer::RenderTargetSupported() const {
  return SDL_RenderTargetSupported(renderer_ptr.get()) == SDL_TRUE;
}

void Renderer::SetRenderTarget(Texture& texture) {
  int return_code = SDL_SetRenderTarget(renderer_ptr.get(), texture.texture_ptr.get());
  if (return_code != 0) {
    throw RendererException("Failed to set render target for the renderer");
  }
}

void Renderer::SetRenderTargetDefault() {
  int return_code = SDL_SetRenderTarget(renderer_ptr.get(), nullptr);
  if (return_code != 0) {
    throw RendererException("Failed to set render target for the renderer");
  }
}

void Renderer::SetLogicalSize(Dimensions dimensions) {
  int return_code =
      SDL_RenderSetLogicalSize(renderer_ptr.get(), dimensions.width, dimensions.height);
  if (return_code != 0) {
    throw RendererException("Failed to set the logical size for the renderer");
  }
}

Dimensions Renderer::GetLogicalSize() const {
  Dimensions dimensions;
  SDL_RenderGetLogicalSize(renderer_ptr.get(), &dimensions.width, &dimensions.height);
  return dimensions;
}

void Renderer::SetIntegerScale(bool is_enabled) {
  int return_code =
      SDL_RenderSetIntegerScale(renderer_ptr.get(), is_enabled ? SDL_TRUE : SDL_FALSE);
  if (return_code != 0) {
    throw RendererException("Failed to set the integer scaling for the renderer");
  }
}

bool Renderer::GetIntegerScale() const {
  return SDL_RenderGetIntegerScale(renderer_ptr.get()) == SDL_TRUE;
}

void Renderer::SetViewport(const Rectangle& rectangle) {
  SDL_Rect rect{rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  int return_code = SDL_RenderSetViewport(renderer_ptr.get(), &rect);
  if (return_code != 0) {
    throw RendererException("Failed to set the viewport for the renderer");
  }
}

void Renderer::ResetViewport() {
  int return_code = SDL_RenderSetViewport(renderer_ptr.get(), nullptr);
  if (return_code != 0) {
    throw RendererException("Failed to set the viewport for the renderer");
  }
}

Rectangle Renderer::GetViewport() const {
  SDL_Rect rect;
  SDL_RenderGetViewport(renderer_ptr.get(), &rect);
  return {rect.x, rect.y, rect.w, rect.h};
}

void Renderer::SetClipRectangle(const Rectangle& rectangle) {
  SDL_Rect rect{rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  int return_code = SDL_RenderSetClipRect(renderer_ptr.get(), &rect);
  if (return_code != 0) {
    throw RendererException("Failed to set the clip rectangle for the renderer");
  }
}

void Renderer::ResetClipRectangle() {
  int return_code = SDL_RenderSetClipRect(renderer_ptr.get(), nullptr);
  if (return_code != 0) {
    throw RendererException("Failed to set the clip rectangle for the renderer");
  }
}

Rectangle Renderer::GetClipRectangle() const {
  SDL_Rect rect;
  SDL_RenderGetClipRect(renderer_ptr.get(), &rect);
  return {rect.x, rect.y, rect.w, rect.h};
}

bool Renderer::IsClipEnabled() const {
  return SDL_RenderIsClipEnabled(renderer_ptr.get()) == SDL_TRUE;
}

void Renderer::SetScale(float scale_x, float scale_y) {
  int return_code = SDL_RenderSetScale(renderer_ptr.get(), scale_x, scale_y);
  if (return_code != 0) {
    throw RendererException("Failed to set scaling for the renderer");
  }
}

std::tuple<float, float> Renderer::GetScale() const {
  float scale_x = NAN, scale_y = NAN;
  SDL_RenderGetScale(renderer_ptr.get(), &scale_x, &scale_y);
  return {scale_x, scale_y};
}

void Renderer::SetDrawColor(Color color) {
  int return_code = SDL_SetRenderDrawColor(renderer_ptr.get(), color.r, color.g, color.b, color.a);
  if (return_code != 0) {
    throw RendererException("Failed to set the draw color for the renderer");
  }
}

Color Renderer::GetColor() const {
  Color color;
  int return_code =
      SDL_GetRenderDrawColor(renderer_ptr.get(), &color.r, &color.g, &color.b, &color.a);
  if (return_code != 0) {
    throw RendererException("Failed to get the draw color for the renderer");
  }
  return color;
}

void Renderer::Clear() {
  int return_code = SDL_RenderClear(renderer_ptr.get());
  if (return_code != 0) {
    throw RendererException("Failed to clear the rendering target");
  }
}

void Renderer::DrawPoint(Point point) {
  int return_code = SDL_RenderDrawPoint(renderer_ptr.get(), point.x, point.y);
  if (return_code != 0) {
    throw RendererException("Failed to draw a point");
  }
}

void Renderer::DrawPoints(const std::vector<Point>& points) {
  std::vector<SDL_Point> raw_points;
  raw_points.reserve(points.size());
  for (const Point& point : points) {
    raw_points.push_back({point.x, point.y});
  }
  int return_code = SDL_RenderDrawPoints(renderer_ptr.get(), raw_points.data(), raw_points.size());
  if (return_code != 0) {
    throw RendererException("Failed to draw multiple points");
  }
}

void Renderer::DrawLine(Point line_start, Point line_end) {
  int return_code =
      SDL_RenderDrawLine(renderer_ptr.get(), line_start.x, line_start.y, line_end.x, line_end.y);
  if (return_code != 0) {
    throw RendererException("Failed to draw a line");
  }
}

void Renderer::DrawLines(const std::vector<Point>& points) {
  std::vector<SDL_Point> raw_points;
  raw_points.reserve(points.size());
  for (const Point& point : points) {
    raw_points.push_back({point.x, point.y});
  }
  int return_code = SDL_RenderDrawLines(renderer_ptr.get(), raw_points.data(), raw_points.size());
  if (return_code != 0) {
    throw RendererException("Failed to draw multiple lines");
  }
}

void Renderer::DrawRectangle(const Rectangle& rectangle) {
  SDL_Rect rect{rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  int return_code = SDL_RenderDrawRect(renderer_ptr.get(), &rect);
  if (return_code != 0) {
    throw RendererException("Failed to draw the rectangle");
  }
}

void Renderer::DrawRectangles(const std::vector<Rectangle>& rectangles) {
  std::vector<SDL_Rect> rects;
  rects.reserve(rectangles.size());
  for (const Rectangle& rectangle : rectangles) {
    rects.push_back({rectangle.x, rectangle.y, rectangle.width, rectangle.height});
  }
  int return_code = SDL_RenderDrawRects(renderer_ptr.get(), rects.data(), rects.size());
  if (return_code != 0) {
    throw RendererException("Failed to draw multiple rectangles");
  }
}

void Renderer::Fill() {
  int return_code = SDL_RenderFillRect(renderer_ptr.get(), NULL);
  if (return_code != 0) {
    throw RendererException("Failed to fill the rectangle");
  }
}

void Renderer::FillRectangle(const Rectangle& rectangle) {
  SDL_Rect rect{rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  int return_code = SDL_RenderFillRect(renderer_ptr.get(), &rect);
  if (return_code != 0) {
    throw RendererException("Failed to fill the rectangle");
  }
}

void Renderer::FillRectangles(const std::vector<Rectangle>& rectangles) {
  std::vector<SDL_Rect> rects;
  rects.reserve(rectangles.size());
  for (const Rectangle& rectangle : rectangles) {
    rects.push_back({rectangle.x, rectangle.y, rectangle.width, rectangle.height});
  }
  int return_code = SDL_RenderFillRects(renderer_ptr.get(), rects.data(), rects.size());
  if (return_code != 0) {
    throw RendererException("Failed to fill multiple rectangles");
  }
}

void Renderer::Copy(const Texture& texture) {
  int return_code = SDL_RenderCopy(renderer_ptr.get(), texture.texture_ptr.get(), nullptr, nullptr);
  if (return_code != 0) {
    throw RendererException("Failed to copy the texture to the current rendering target");
  }
}

void Renderer::Copy(const Texture& texture, const Rectangle& dest) {
  SDL_Rect dstrect{dest.x, dest.y, dest.width, dest.height};
  int return_code =
      SDL_RenderCopy(renderer_ptr.get(), texture.texture_ptr.get(), nullptr, &dstrect);
  if (return_code != 0) {
    throw RendererException("Failed to copy the texture to the current rendering target");
  }
}

void Renderer::Copy(const Texture& texture, const Rectangle& source, const Rectangle& dest) {
  SDL_Rect srcrect{source.x, source.y, source.width, source.height};
  SDL_Rect dstrect{dest.x, dest.y, dest.width, dest.height};
  int return_code =
      SDL_RenderCopy(renderer_ptr.get(), texture.texture_ptr.get(), &srcrect, &dstrect);
  if (return_code != 0) {
    throw RendererException("Failed to copy the texture to the current rendering target");
  }
}

void Renderer::Copy(const Texture& texture, double angle, Renderer::Flip flip) {
  SDL_RendererFlip flip_value = static_cast<SDL_RendererFlip>(flip);
  int return_code = SDL_RenderCopyEx(renderer_ptr.get(), texture.texture_ptr.get(), nullptr,
                                     nullptr, angle, nullptr, flip_value);
  if (return_code != 0) {
    throw RendererException("Failed to copy the texture to the current rendering target");
  }
}

void Renderer::Copy(const Texture& texture, double angle, Point center, Renderer::Flip flip) {
  SDL_Point center_value{center.x, center.y};
  SDL_RendererFlip flip_value = static_cast<SDL_RendererFlip>(flip);
  int return_code = SDL_RenderCopyEx(renderer_ptr.get(), texture.texture_ptr.get(), nullptr,
                                     nullptr, angle, &center_value, flip_value);
  if (return_code != 0) {
    throw RendererException("Failed to copy the texture to the current rendering target");
  }
}

void Renderer::Copy(const Texture& texture, const Rectangle& dest, double angle,
                    Renderer::Flip flip) {
  SDL_Rect dstrect{dest.x, dest.y, dest.width, dest.height};
  SDL_RendererFlip flip_value = static_cast<SDL_RendererFlip>(flip);
  int return_code = SDL_RenderCopyEx(renderer_ptr.get(), texture.texture_ptr.get(), nullptr,
                                     &dstrect, angle, nullptr, flip_value);
  if (return_code != 0) {
    throw RendererException("Failed to copy the texture to the current rendering target");
  }
}

void Renderer::Copy(const Texture& texture, const Rectangle& source, const Rectangle& dest,
                    double angle, Renderer::Flip flip) {
  SDL_Rect srcrect{source.x, source.y, source.width, source.height};
  SDL_Rect dstrect{dest.x, dest.y, dest.width, dest.height};
  SDL_RendererFlip flip_value = static_cast<SDL_RendererFlip>(flip);
  int return_code = SDL_RenderCopyEx(renderer_ptr.get(), texture.texture_ptr.get(), &srcrect,
                                     &dstrect, angle, nullptr, flip_value);
  if (return_code != 0) {
    throw RendererException("Failed to copy the texture to the current rendering target");
  }
}

void Renderer::Copy(const Texture& texture, const Rectangle& dest, double angle, Point center,
                    Renderer::Flip flip) {
  SDL_Rect dstrect{dest.x, dest.y, dest.width, dest.height};
  SDL_Point center_value{center.x, center.y};
  SDL_RendererFlip flip_value = static_cast<SDL_RendererFlip>(flip);
  int return_code = SDL_RenderCopyEx(renderer_ptr.get(), texture.texture_ptr.get(), nullptr,
                                     &dstrect, angle, &center_value, flip_value);
  if (return_code != 0) {
    throw RendererException("Failed to copy the texture to the current rendering target");
  }
}

void Renderer::Copy(const Texture& texture, const Rectangle& source, const Rectangle& dest,
                    double angle, Point center, Renderer::Flip flip) {
  SDL_Rect srcrect{source.x, source.y, source.width, source.height};
  SDL_Rect dstrect{dest.x, dest.y, dest.width, dest.height};
  SDL_Point center_value{center.x, center.y};
  SDL_RendererFlip flip_value = static_cast<SDL_RendererFlip>(flip);
  int return_code = SDL_RenderCopyEx(renderer_ptr.get(), texture.texture_ptr.get(), &srcrect,
                                     &dstrect, angle, &center_value, flip_value);
  if (return_code != 0) {
    throw RendererException("Failed to copy the texture to the current rendering target");
  }
}

void Renderer::ReadPixels(uint32_t format, void* pixels, int pitch) {
  int return_code =
      SDL_RenderReadPixels(renderer_ptr.get(), nullptr, static_cast<Uint32>(format), pixels, pitch);
  if (return_code != 0) {
    throw RendererException("Failed to read pixels from the current rendering target");
  }
}

void Renderer::ReadPixels(const Rectangle& rectangle, uint32_t format, void* pixels, int pitch) {
  SDL_Rect rect{rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  int return_code =
      SDL_RenderReadPixels(renderer_ptr.get(), &rect, static_cast<Uint32>(format), pixels, pitch);
  if (return_code != 0) {
    throw RendererException("Failed to read pixels from the current rendering target");
  }
}

void Renderer::RenderPresent() { SDL_RenderPresent(renderer_ptr.get()); }

void Renderer::Render(Renderable& renderable) { renderable.Render(*this); }

SDL_Renderer* Renderer::Release() { return renderer_ptr.release(); }

void Renderer::Deleter::operator()(SDL_Renderer* ptr) const {
  if (ptr != nullptr) {
    SDL_DestroyRenderer(ptr);
  }
}
