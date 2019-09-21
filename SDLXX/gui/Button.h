#ifndef SDLXX_BUTTON_H
#define SDLXX_BUTTON_H

#include "../base/Point.h"
#include "../base/Object.h"

namespace SDLXX {
    class Button : public Object {
    public:
        Button(int x = 0, int y = 0, int width = 0, int height = 0);

        ~Button();

        void setRelativePosition(int x, int y);

        void setRelativeSize(int x, int y);

        bool handleEvent(Event &e) override;

        void update(Uint32 t, Uint32 dt, const Dimensions &windowDimensions) override;

        void render(Renderer &renderer) override;

        void setText(const std::string &text, SDL_Renderer *renderer);

    private:
        std::string text;
        Point absPos, relPos;
        Dimensions absDim, relDim, windowDim;
        Texture *textTexture = nullptr;
        bool mouseOver = false;
    };
}

#endif // SDLXX_BUTTON_H
