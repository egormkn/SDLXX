#ifndef SDLXX_RENDERER_H
#define SDLXX_RENDERER_H

#include <SDL_render.h>
#include "Exception.h"
#include "Color.h"
#include "Log.h"
#include "Texture.h"
#include "Rectangle.h"

namespace SDLXX {
    class Renderer {
    public:
        Renderer(SDL_Renderer *r);

        Renderer(SDL_Window *w, int driver, Uint32 flags);

        ~Renderer();

        SDL_Renderer *getSDLRenderer() const;

        void setColor(const Color &color);

        void render();

        void clear();

        void renderCopy(const Texture &texture, const SDL_Rect *src = NULL, const SDL_Rect *dest = NULL);

        void renderCopy(const Texture &texture, const Rectangle &src, const Rectangle &dest);

        void fillRect(SDL_Rect *rect);

    private:
        SDL_Renderer *renderer = nullptr;
    };
}

#endif // SDLXX_RENDERER_H
