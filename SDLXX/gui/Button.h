#ifndef SDLXX_BUTTON_H
#define SDLXX_BUTTON_H

#include "../base/Point.h"
#include "../base/Object.h"

namespace SDLXX {
    class Button : public Object {
    public:
        Button(int x = 0, int y = 0, int width = 0, int height = 0) {
            absPos.setPoint(x, y);
            absDim.setPoint(width, height);
        }

        void setRelativePosition(int x, int y) {
            relPos.setPoint(x, y);
        }

        bool handleEvent(Event &e) override {
            SDL_Rect fillRect = {
                    (int) (relPos.getX() * windowDim.getX() / 100.0f) + absPos.getX(),
                    (int) (relPos.getY() * windowDim.getY() / 100.0f) + absPos.getY(),
                    (int) (relDim.getX() * windowDim.getX() / 100.0f) + absDim.getX(),
                    (int) (relDim.getY() * windowDim.getY() / 100.0f) + absDim.getY()
            };


            bool inside = true;
            switch (e.getType()) {
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(x < fillRect.x) {
                        inside = false;
                    }
                        //Mouse is right of the button
                    else if(x > fillRect.x + fillRect.w) {
                        inside = false;
                    }
                        //Mouse above the button
                    else if(y < fillRect.y) {
                        inside = false;
                    }
                        //Mouse below the button
                    else if(y > fillRect.y + fillRect.h) {
                        inside = false;
                    }
                    mouseOver = inside;
                    if (e.getType() == SDL_MOUSEBUTTONDOWN) {
                        Log::log(std::to_string(windowDim.getX()));
                    }
                    return inside;
                default:
                    return false;
            }
        }

        void update(Uint32 t, Uint32 dt, const Dimensions &windowDimensions) override {
            windowDim.setPoint(windowDimensions.getX(), windowDimensions.getY());
        }

        void render(Renderer &renderer) override {
            SDL_Rect fillRect = {
                    (int) (relPos.getX() * windowDim.getX() / 100.0f) + absPos.getX(),
                    (int) (relPos.getY() * windowDim.getY() / 100.0f) + absPos.getY(),
                    (int) (relDim.getX() * windowDim.getX() / 100.0f) + absDim.getX(),
                    (int) (relDim.getY() * windowDim.getY() / 100.0f) + absDim.getY()
            };

            renderer.setColor(mouseOver ? Color(0xFF8888FF) : Color(0xCCCCCCFF));
            renderer.fillRect(&fillRect);
        }

        void setText(const std::string &text) {
            Button::text = text;
        }

    private:
        std::string text;
        Point absPos, relPos;
        Dimensions absDim, relDim, windowDim;

        bool mouseOver = false;
    };
}

#endif //SDLXX_BUTTON_H
