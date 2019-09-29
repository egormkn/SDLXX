#include <numeric>
#include <stdexcept>

#include <SDL_render.h>
#include <sdlxx/core/Renderer.h>

using namespace sdlxx::core;

Renderer::Renderer(Window& window, int driver,
                   const std::unordered_set<Option>& options) {
  Uint32 flags = std::accumulate(options.begin(), options.end(), 0,
                                 [](Uint32 flags, const Option& option) {
                                   return flags | static_cast<uint32_t>(option);
                                 });
  renderer_ptr = SDL_CreateRenderer(static_cast<SDL_Window*>(window.window_ptr),
                                    driver, flags);
  if (!renderer_ptr) {
    // std::cout << "Could not create hardware accelerated renderer, trying "
    //              "software fallback";
    renderer_ptr = SDL_CreateRenderer(
        static_cast<SDL_Window*>(window.window_ptr), -1, SDL_RENDERER_SOFTWARE);
    if (!renderer_ptr) {
      throw std::runtime_error("Renderer could not be created" +
                               std::string(SDL_GetError()));
    }
  }
}

Renderer::Renderer(void* window, int driver,
                   const std::unordered_set<Option>& options) {
  Uint32 flags = std::accumulate(options.begin(), options.end(), 0,
                                 [](Uint32 flags, const Option& option) {
                                   return flags | static_cast<uint32_t>(option);
                                 });
  renderer_ptr =
      SDL_CreateRenderer(static_cast<SDL_Window*>(window), driver, flags);
  if (!renderer_ptr) {
    // std::cout << "Could not create hardware accelerated renderer, trying "
    //              "software fallback";
    renderer_ptr = SDL_CreateRenderer(static_cast<SDL_Window*>(window), -1,
                                      SDL_RENDERER_SOFTWARE);
    if (!renderer_ptr) {
      throw std::runtime_error("Renderer could not be created" +
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

Renderer::~Renderer() {
  if (renderer_ptr) {
    SDL_DestroyRenderer(static_cast<SDL_Renderer*>(renderer_ptr));
    renderer_ptr = nullptr;
  }
}

void Renderer::setLogicalSize(int width, int height) {
  SDL_RenderSetLogicalSize(static_cast<SDL_Renderer*>(renderer_ptr), width,
                           height);
}

void Renderer::setColor(const Color& color) {
  int result =
      SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(renderer_ptr),
                             color.red, color.green, color.blue, color.alpha);
  if (result != 0) {
    throw std::runtime_error("Failed to set color for renderer: " +
                             std::string(SDL_GetError()));
  }
}

// SDL_Renderer* Renderer::getSDLRenderer() const { return renderer; }

void Renderer::render() {
  SDL_RenderPresent(static_cast<SDL_Renderer*>(renderer_ptr));
}

void Renderer::clear() {
  SDL_RenderClear(static_cast<SDL_Renderer*>(renderer_ptr));
}

// void Renderer::renderCopy(const Texture& texture, const SDL_Rect* src,
//                           const SDL_Rect* dest) {
//   int result = SDL_RenderCopy(renderer, texture.getSDLTexture(), src, dest);
//   if (result < 0) {
//     throw Exception("Failed to render a texture");
//   }
// }

void Renderer::renderCopy(const Texture& texture, const Rectangle& src,
                          const Rectangle& dest) {
  int result = SDL_RenderCopy(static_cast<SDL_Renderer*>(renderer_ptr),
                              texture.getSDLTexture(), src.getSDLRectangle(),
                              dest.getSDLRectangle());
  if (result < 0) {
    throw std::runtime_error("Failed to render a texture");
  }
}

void Renderer::renderCopy(const Texture& texture, const Rectangle& dest) {
  int result =
      SDL_RenderCopy(static_cast<SDL_Renderer*>(renderer_ptr),
                     texture.getSDLTexture(), nullptr, dest.getSDLRectangle());
  if (result < 0) {
    throw std::runtime_error("Failed to render a texture");
  }
}

void Renderer::fillRect(const Rectangle& rectangle) {
  SDL_RenderFillRect(static_cast<SDL_Renderer*>(renderer_ptr),
                     rectangle.getSDLRectangle());
}
