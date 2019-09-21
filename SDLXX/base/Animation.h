#ifndef SDLXX_ANIMATION_H
#define SDLXX_ANIMATION_H

#include <vector>
#include "Texture.h"
#include "Renderer.h"

namespace SDLXX {

    struct Fragment {
        int lengthOfLine;
        int heightOfLine;
        int widthOfFrame;
    };

    class Animation { // TODO
    public:
        // Animation(Texture *texture, std::vector<Fragments> &fragments);

        SDL_Rect setState(int number);

        void update(double t, double dt);

        void render(SDLXX::Renderer *renderer, SDL_Rect *rect);

    private:
        std::vector<std::vector<SDL_Rect>> mainRect;
        SDLXX::Texture *ourTexture = nullptr;
    };
}

#endif // SDLXX_ANIMATION_H
