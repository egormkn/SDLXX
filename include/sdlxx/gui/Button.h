#ifndef SDLXX_BUTTON_H
#define SDLXX_BUTTON_H

#include "../core/Point.h"
#include "../core/Object.h"

namespace sdlxx::gui {
    class Button : public sdlxx::core::Object {
    public:
        Button(int x = 0, int y = 0, int width = 0, int height = 0);

        ~Button();

        void setRelativePosition(int x, int y);

        void setRelativeSize(int x, int y);

        bool handleEvent(sdlxx::core::Event &e) override;

        void update(Uint32 t, Uint32 dt, const sdlxx::core::Dimensions &windowDimensions) override;

        void render(sdlxx::core::Renderer &renderer) override;

        void setText(const std::string &text, SDL_Renderer *renderer);

    private:
        std::string text;
        sdlxx::core::Point absPos, relPos;
        sdlxx::core::Dimensions absDim, relDim, windowDim;
        sdlxx::core::Texture *textTexture = nullptr;
        bool mouseOver = false;
    };
}

#endif // SDLXX_BUTTON_H
