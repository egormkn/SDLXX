#include <numeric>

#include <SDL_render.h>
#include <sdlxx/core/Renderer.h>
#include <stdexcept>


using namespace sdlxx::core;

Renderer::Renderer(Window& window, int driver,
                   const std::unordered_set<Option>& options) {
  Uint32 flags = std::accumulate(options.begin(), options.end(), 0,
                                 [](Uint32 flags, const Option& option) {
                                   return flags | static_cast<uint32_t>(option);
                                 });
  renderer =
      SDL_CreateRenderer(static_cast<SDL_Window*>(window.window), driver, flags);
  if (renderer == nullptr) {
    // std::cout << "Could not create hardware accelerated renderer, trying "
    //              "software fallback";
    renderer = SDL_CreateRenderer(static_cast<SDL_Window*>(window.window), -1,
                                  SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr) {
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
  renderer =
      SDL_CreateRenderer(static_cast<SDL_Window*>(window), driver, flags);
  if (renderer == nullptr) {
    // std::cout << "Could not create hardware accelerated renderer, trying "
    //              "software fallback";
    renderer = SDL_CreateRenderer(static_cast<SDL_Window*>(window), -1,
                                  SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr) {
      throw std::runtime_error("Renderer could not be created" +
                               std::string(SDL_GetError()));
    }
  }
}

Renderer::~Renderer() {
  if (renderer != nullptr) {
    SDL_DestroyRenderer(static_cast<SDL_Renderer*>(renderer));
    renderer = nullptr;
  }
}

void Renderer::setLogicalSize(int width, int height) {
  SDL_RenderSetLogicalSize(static_cast<SDL_Renderer*>(renderer), width, height);
}

void Renderer::setColor(const Color& color) {
  int result =
      SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(renderer), color.red,
                             color.green, color.blue, color.alpha);
  if (result != 0) {
    throw std::runtime_error("Failed to set color for renderer: " +
                             std::string(SDL_GetError()));
  }
}

// SDL_Renderer* Renderer::getSDLRenderer() const { return renderer; }

void Renderer::render() { SDL_RenderPresent(static_cast<SDL_Renderer*>(renderer)); }

void Renderer::clear() { SDL_RenderClear(static_cast<SDL_Renderer*>(renderer)); }

// void Renderer::renderCopy(const Texture& texture, const SDL_Rect* src,
//                           const SDL_Rect* dest) {
//   int result = SDL_RenderCopy(renderer, texture.getSDLTexture(), src, dest);
//   if (result < 0) {
//     throw Exception("Failed to render a texture");
//   }
// }

void Renderer::renderCopy(const Texture& texture, const Rectangle& src,
                          const Rectangle& dest) {
  int result = SDL_RenderCopy(static_cast<SDL_Renderer*>(renderer), texture.getSDLTexture(),
                              src.getSDLRectangle(), dest.getSDLRectangle());
  if (result < 0) {
    throw std::runtime_error("Failed to render a texture");
  }
}

void Renderer::renderCopy(const Texture& texture,
                          const Rectangle& dest) {
  int result = SDL_RenderCopy(static_cast<SDL_Renderer*>(renderer), texture.getSDLTexture(),
                              nullptr, dest.getSDLRectangle());
  if (result < 0) {
    throw std::runtime_error("Failed to render a texture");
  }
}

void Renderer::fillRect(const Rectangle& rectangle) {
  SDL_RenderFillRect(static_cast<SDL_Renderer*>(renderer),
                     rectangle.getSDLRectangle());
}
