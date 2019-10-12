#include <sdlxx/gui/Animation.h>

/*sdlxx::core::Animation::Animation(sdlxx::core::Texture *texture, std::vector<Fragments> &fragments) {
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
}*/


SDL_Rect sdlxx::core::Animation::setState(int number) {
    return mainRect[number][0];
}

void sdlxx::core::Animation::update(double t, double dt) {

}

void sdlxx::core::Animation::render(sdlxx::core::Renderer *renderer, SDL_Rect *rect) {
    SDL_Rect tmpRect = {0, 0, 0, 0};
    if (rect != nullptr) {
        tmpRect.w = rect -> w;
        tmpRect.h = rect -> h;
        tmpRect.x = rect -> x;
        tmpRect.y = rect -> y;
    }

    // renderer->renderCopy(ourTexture, rect, tmpRect);
}
