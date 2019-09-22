#include <sdlxx/core/Renderer.h>

sdlxx::core::Renderer::Renderer(SDL_Renderer *r) : renderer(r) {}

sdlxx::core::Renderer::Renderer(SDL_Window *w, int driver, Uint32 flags) {
    renderer = SDL_CreateRenderer(w, driver, flags);
    if(renderer == nullptr) {
        Log::warning("Could not create hardware accelerated renderer, trying software fallback");
        renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_SOFTWARE);
        if(renderer == nullptr) {
            throw Exception("Renderer could not be created", SDL_GetError());
        }
    }
}

sdlxx::core::Renderer::~Renderer() {
    if(renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
}

SDL_Renderer *sdlxx::core::Renderer::getSDLRenderer() const {
    return renderer;
}

void sdlxx::core::Renderer::setColor(const sdlxx::core::Color &color) {
    SDL_SetRenderDrawColor(renderer, color.r(), color.g(), color.b(), color.a());
}

void sdlxx::core::Renderer::render() {
    SDL_RenderPresent(renderer);
}

void sdlxx::core::Renderer::clear() {
    SDL_RenderClear(renderer);
}

void sdlxx::core::Renderer::renderCopy(const sdlxx::core::Texture &texture, const SDL_Rect *src, const SDL_Rect *dest) {
    int result = SDL_RenderCopy(renderer, texture.getSDLTexture(), src, dest);
    if (result < 0) {
        throw Exception("Failed to render a texture");
    }
}

void
sdlxx::core::Renderer::renderCopy(const sdlxx::core::Texture &texture, const sdlxx::core::Rectangle &src, const sdlxx::core::Rectangle &dest) {
    int result = SDL_RenderCopy(renderer, texture.getSDLTexture(), src.getSDLRectangle(), dest.getSDLRectangle());
    if (result < 0) {
        throw Exception("Failed to render a texture");
    }
}

void sdlxx::core::Renderer::fillRect(SDL_Rect *rect) {
    SDL_RenderFillRect(renderer, rect);
}
