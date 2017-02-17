#ifndef SDLXX_ANIMATION_H
#define SDLXX_ANIMATION_H

#include "Texture.h"

namespace SDLXX {
    struct Fragment {
        int lengthOfLine;
        int heightOfLine;
        int widthOfFrame;
    };

    class Animation {
    public:
/*        Animation(Texture *texture, std::vector<Fragments> &fragments) {
            ourTexture = texture;
            int counter = 0;
            int mainX = 0, mainY = 0;
            mainRect.resize(fragments.size());
            for (int i = 0; i < fragments.size(); i++) {
                counter = fragments[i].lengthOfLine / fragments[i].widthOfFrame;
                SDL_Rect tmpRect;
                for (int j = 0; j < counter; j++) {
                    tmpRect = { mainX, mainY, fragments[i].widthOfFrame, fragments[i].heightOfLine};
                    mainRect[i].push_back(tmpRect);
                    mainX += fragments[i].widthOfFrame;
                }
                mainY += fragments[i].heightOfLine;
                mainX = 0;
            }
        }

        SDL_Rect setState(int number) {
            return mainRect[number][0];
        }

        void update(double t, double dt) {

        }

        void render(SDLXX::Renderer *renderer, SDL_Rect *rect) {
            SDL_Rect tmpRect = {0, 0, 0, 0};
            if (rect != NULL) {
                tmpRect.w = rect -> w;
                tmpRect.h = rect -> h;
                tmpRect.x = rect -> x;
                tmpRect.y = rect -> y;
            }

            render -> renderCopy(ourTexture, rect, tmpRect);
        }

    private:
        std::vector<std::vector<SDL_Rect>> mainRect;
        SDLXX::Texture *ourTexture = NULL;*/
    };
}

#endif // SDLXX_ANIMATION_H
