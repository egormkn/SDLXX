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

        ~Button() {
            if (textTexture != nullptr) {
                delete textTexture;
            }
        }

        void setRelativePosition(int x, int y) {
            relPos.setPoint(x, y);
        }

        void setRelativeSize(int x, int y) {
            relDim.setPoint(x, y);
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
                    return inside;
                default:
                    return false;
            }
        }

        void update(Uint32 t, Uint32 dt, const Dimensions &windowDimensions) override {
            windowDim.setPoint(windowDimensions.getX(), windowDimensions.getY());
        }

        void render(Renderer &renderer) override {
            int w = (int) (relDim.getX() * windowDim.getX() / 100.0f) + absDim.getX();
            int h = (int) (relDim.getY() * windowDim.getY() / 100.0f) + absDim.getY();
            SDL_Rect fillRect = {
                    (int) (relPos.getX() * windowDim.getX() / 100.0f) + absPos.getX(),
                    (int) (relPos.getY() * windowDim.getY() / 100.0f) + absPos.getY(),
                    (int) (relDim.getX() * windowDim.getX() / 100.0f) + absDim.getX(),
                    (int) (relDim.getY() * windowDim.getY() / 100.0f) + absDim.getY()
            };

            renderer.setColor(mouseOver ? Color(0xFF8888FF) : Color(0xCCCCCCFF));
            renderer.fillRect(&fillRect);

            SDL_Rect fillRect2 = {
                    (int) (relPos.getX() * windowDim.getX() / 100.0f) + absPos.getX() + (w - textTexture->getWidth()) / 2,
                    (int) (relPos.getY() * windowDim.getY() / 100.0f) + absPos.getY() + (h - textTexture->getHeight()) / 2,
                    textTexture->getWidth(),
                    textTexture->getHeight()

            };

            renderer.renderCopy(*textTexture, NULL, &fillRect2);
        }

        void setText(const std::string &text, SDL_Renderer *renderer) {
            Button::text = text;
            if (textTexture != nullptr) {
                delete textTexture;
            }
            textTexture = new Texture(text, Color(), Font("resources/OpenSans.ttf", 16), renderer);
        }

    private:
        std::string text;
        Point absPos, relPos;
        Dimensions absDim, relDim, windowDim;
        Texture *textTexture = nullptr;
        bool mouseOver = false;
    };
}

#endif // SDLXX_BUTTON_H
