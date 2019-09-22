#include <sdlxx/gui/Button.h>

sdlxx::gui::Button::Button(int x, int y, int width, int height) {
    absPos.setPoint(x, y);
    absDim.setPoint(width, height);
}

sdlxx::gui::Button::~Button() {
    if (textTexture != nullptr) {
        delete textTexture;
    }
}

void sdlxx::gui::Button::setRelativePosition(int x, int y) {
    relPos.setPoint(x, y);
}

void sdlxx::gui::Button::setRelativeSize(int x, int y) {
    relDim.setPoint(x, y);
}

bool sdlxx::gui::Button::handleEvent(sdlxx::core::Event &e) {
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

void sdlxx::gui::Button::update(Uint32 t, Uint32 dt, const sdlxx::core::Dimensions &windowDimensions) {
    windowDim.setPoint(windowDimensions.getX(), windowDimensions.getY());
}

void sdlxx::gui::Button::render(sdlxx::core::Renderer &renderer) {
    int w = (int) (relDim.getX() * windowDim.getX() / 100.0f) + absDim.getX();
    int h = (int) (relDim.getY() * windowDim.getY() / 100.0f) + absDim.getY();
    SDL_Rect fillRect = {
            (int) (relPos.getX() * windowDim.getX() / 100.0f) + absPos.getX(),
            (int) (relPos.getY() * windowDim.getY() / 100.0f) + absPos.getY(),
            (int) (relDim.getX() * windowDim.getX() / 100.0f) + absDim.getX(),
            (int) (relDim.getY() * windowDim.getY() / 100.0f) + absDim.getY()
    };

    renderer.setColor(mouseOver ? sdlxx::core::Color(0xFF8888FF) : sdlxx::core::Color(0xCCCCCCFF));
    renderer.fillRect(&fillRect);

    SDL_Rect fillRect2 = {
            (int) (relPos.getX() * windowDim.getX() / 100.0f) + absPos.getX() + (w - textTexture->getWidth()) / 2,
            (int) (relPos.getY() * windowDim.getY() / 100.0f) + absPos.getY() + (h - textTexture->getHeight()) / 2,
            textTexture->getWidth(),
            textTexture->getHeight()

    };

    renderer.renderCopy(*textTexture, NULL, &fillRect2);
}

void sdlxx::gui::Button::setText(const std::string &text, SDL_Renderer *renderer) {
    Button::text = text;
    if (textTexture != nullptr) {
        delete textTexture;
    }
    textTexture = new sdlxx::core::Texture(text, sdlxx::core::Color(), sdlxx::ttf::Font("resources/OpenSans.ttf", 16), renderer);
}
