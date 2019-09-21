#include "Button.h"

SDLXX::Button::Button(int x, int y, int width, int height) {
    absPos.setPoint(x, y);
    absDim.setPoint(width, height);
}

SDLXX::Button::~Button() {
    if (textTexture != nullptr) {
        delete textTexture;
    }
}

void SDLXX::Button::setRelativePosition(int x, int y) {
    relPos.setPoint(x, y);
}

void SDLXX::Button::setRelativeSize(int x, int y) {
    relDim.setPoint(x, y);
}

bool SDLXX::Button::handleEvent(SDLXX::Event &e) {
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

void SDLXX::Button::update(Uint32 t, Uint32 dt, const SDLXX::Dimensions &windowDimensions) {
    windowDim.setPoint(windowDimensions.getX(), windowDimensions.getY());
}

void SDLXX::Button::render(SDLXX::Renderer &renderer) {
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

void SDLXX::Button::setText(const std::string &text, SDL_Renderer *renderer) {
    Button::text = text;
    if (textTexture != nullptr) {
        delete textTexture;
    }
    textTexture = new Texture(text, Color(), Font("resources/OpenSans.ttf", 16), renderer);
}
