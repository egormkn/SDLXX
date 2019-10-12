#include <numeric>
#include <sstream>
#include <stdexcept>

#include <SDL_render.h>
#include <sdlxx/core/Rectangle.h>
#include <sdlxx/core/Renderer.h>
#include <sdlxx/core/Surface.h>

using namespace sdlxx::core;

// Convert options into bit mask
Uint32 getFlagsMask(const std::unordered_set<Renderer::Option>& options) {
  return std::accumulate(options.begin(), options.end(), 0,
                         [](Uint32 flags, const Renderer::Option& option) {
                           return flags | static_cast<uint32_t>(option);
                         });
}

Renderer::Renderer(Surface& surface) {
  renderer_ptr = SDL_CreateSoftwareRenderer(
      static_cast<SDL_Surface*>(surface.surface_ptr));
  if (!renderer_ptr) {
    throw std::runtime_error("Renderer could not be created: " +
                             std::string(SDL_GetError()));
  }
}

Renderer::~Renderer() {
  if (renderer_ptr) {
    SDL_DestroyRenderer(static_cast<SDL_Renderer*>(renderer_ptr));
    renderer_ptr = nullptr;
  }
}

void Renderer::setLogicalSize(int width, int height) {
  int return_code = SDL_RenderSetLogicalSize(
      static_cast<SDL_Renderer*>(renderer_ptr), width, height);
  if (return_code != 0) {
    throw std::runtime_error("Failed to set the logical size: " +
                             std::string(SDL_GetError()));
  }
}

Dimensions Renderer::getLogicalSize() {
  int w, h;
  SDL_RenderGetLogicalSize(static_cast<SDL_Renderer*>(renderer_ptr), &w, &h);
  Dimensions dimensions(w, h);
  return dimensions;
}

void Renderer::setIntegerScale(bool enable) {
  int return_code = SDL_RenderSetIntegerScale(
      static_cast<SDL_Renderer*>(renderer_ptr), enable ? SDL_TRUE : SDL_FALSE);
  if (return_code != 0) {
    throw std::runtime_error("Failed to set the integer scaling: " +
                             std::string(SDL_GetError()));
  }
}

bool Renderer::getIntegerScale() {
  return SDL_RenderGetIntegerScale(static_cast<SDL_Renderer*>(renderer_ptr)) ==
         SDL_TRUE;
}

// TODO: Implement some methods

void Renderer::setColor(const Color& color) {
  int return_code =
      SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(renderer_ptr), color.r,
                             color.g, color.b, color.a);
  if (return_code != 0) {
    throw std::runtime_error("Failed to set the color: " +
                             std::string(SDL_GetError()));
  }
}

void Renderer::clear() {
  SDL_RenderClear(static_cast<SDL_Renderer*>(renderer_ptr));
}

void Renderer::fillRectangle(const Rectangle& rectangle) {
  SDL_Rect rect{rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  int return_code =
      SDL_RenderFillRect(static_cast<SDL_Renderer*>(renderer_ptr), &rect);
  if (return_code != 0) {
    throw std::runtime_error("Failed to fill the rectangle: " +
                             std::string(SDL_GetError()));
  }
}

void Renderer::copy(const Texture& texture,
                    const std::optional<Rectangle>& source,
                    const std::optional<Rectangle>& destination, double angle,
                    const std::optional<Point>& center, Flip flip) {
  SDL_Rect src, dst;
  SDL_Point c;
  if (source) {
    src = {source->x, source->y, source->width, source->height};
  }
  if (destination) {
    dst = {destination->x, destination->y, destination->width,
           destination->height};
  }
  if (center) {
    c = {center->x, center->y};
  }
  int return_code = SDL_RenderCopyEx(
      static_cast<SDL_Renderer*>(renderer_ptr),
      static_cast<SDL_Texture*>(texture.texture_ptr), source ? &src : nullptr,
      destination ? &dst : nullptr, angle, center ? &c : nullptr,
      static_cast<SDL_RendererFlip>(flip));
  if (return_code < 0) {
    throw std::runtime_error("Failed to render the texture: " +
                             std::string(SDL_GetError()));
  }
}

void Renderer::render() {
  SDL_RenderPresent(static_cast<SDL_Renderer*>(renderer_ptr));
}

Renderer::Renderer(void* window_ptr, int driver,
                   const std::unordered_set<Option>& options) {
  Uint32 flags = getFlagsMask(options);
  renderer_ptr =
      SDL_CreateRenderer(static_cast<SDL_Window*>(window_ptr), driver, flags);
  if (!renderer_ptr) {
    // std::cout << "Could not create hardware accelerated renderer, trying "
    //              "software fallback";
    renderer_ptr = SDL_CreateRenderer(static_cast<SDL_Window*>(window_ptr), -1,
                                      SDL_RENDERER_SOFTWARE);
    if (!renderer_ptr) {
      throw std::runtime_error("Renderer could not be created: " +
                               std::string(SDL_GetError()));
    }
  }
}

Renderer::Renderer(void* renderer_ptr) {
  if (!renderer_ptr) {
    throw std::runtime_error("Renderer could not be instantiated from nullptr");
  }
  this->renderer_ptr = renderer_ptr;
}

Renderer::OptionSet sdlxx::core::operator|(const Renderer::Option& lhs,
                                           const Renderer::Option& rhs) {
  return {lhs, rhs};
}

Renderer::OptionSet sdlxx::core::operator|(Renderer::OptionSet&& lhs,
                                           const Renderer::Option& rhs) {
  lhs.insert(rhs);
  return lhs;
}
