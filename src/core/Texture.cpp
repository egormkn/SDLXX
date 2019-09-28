#include <sdlxx/core/Texture.h>

using namespace sdlxx::core;

Texture::Texture(SDL_Texture *t) {
    texture = t;
    SDL_QueryTexture(t, &format, &access, &width, &height);
}

Texture::Texture(const std::string &path, const Renderer& renderer, int w, int h) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if(surface == nullptr) {
        throw Exception("Unable to load image", IMG_GetError());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

    /*if (w > 0 && h > 0) {
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = w;
        stretchRect.h = h;
        SDL_Surface *scaled = SDL_CreateRGBSurface(0, w, h, 32, 0,0,0,0);
        SDL_BlitScaled(surface, NULL, scaled, &stretchRect);
        SDL_SetColorKey(scaled, SDL_TRUE, SDL_MapRGB(scaled->format, 0, 0xFF, 0xFF));
        SDL_FreeSurface(surface);
        surface = scaled;
    }*/

    texture = SDL_CreateTextureFromSurface(static_cast<SDL_Renderer*>(renderer.renderer), surface);
    if(texture == nullptr) {
        throw Exception("Unable to create texture", SDL_GetError());
    }
    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);
}

Texture::Texture(const std::string &text, const Color &color, const sdlxx::ttf::Font &font,
                        const Renderer& renderer) {
    Surface surface = font.render(text, sdlxx::ttf::TTF_MODE_BLENDED, color);
    texture = SDL_CreateTextureFromSurface(static_cast<SDL_Renderer*>(renderer.renderer), surface.getSDLSurface());
    if(texture == nullptr) {
        throw Exception("Unable to create texture", SDL_GetError());
    }
    width = surface.getWidth();
    height = surface.getHeight();
}

Texture::~Texture() {
    width = 0;
    height = 0;
    access = SDL_TEXTUREACCESS_STATIC;
    format = SDL_PIXELFORMAT_UNKNOWN;
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::render(SDL_Renderer *renderer, SDL_Rect *clip, SDL_Rect *dest, double angle, SDL_Point *center,
                            SDL_RendererFlip flip) {
    //Set rendering space and render to screen


    //Render to screen
    SDL_RenderCopyEx(renderer, texture, clip, dest, angle, center, flip);
}

void Texture::fill(SDL_Renderer *renderer, SDL_Rect *clip, SDL_Rect *dest, double angle, SDL_Point *center,
                          SDL_RendererFlip flip) {

    if (dest == nullptr) {
        SDL_RenderCopyEx(renderer, texture, clip, dest, angle, center, flip);
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

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}

SDL_Texture *Texture::getSDLTexture() const {
    return texture;
}
