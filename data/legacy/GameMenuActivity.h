#pragma once
#ifndef GAMEMENUACTIVITY_H
#define GAMEMENUACTIVITY_H

#include "Activity.h"
#include "GameScreenActivity.h"

class GameMenuActivity : public Activity {
public:
    GameMenuActivity(SDL_Window *gWindow, SDL_Renderer *gRenderer)
            : Activity("Main menu", gWindow, gRenderer) {}

    virtual void render() {
        Activity::render();
    }

    virtual void handleEvent(SDL_Event &e) {
        if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_RIGHT) {
                runIntent(new GameScreenActivity(pWindow, pRenderer));
            } else {
                setActive(false);
            }
        }
    }

};


#endif /* GAMEMENUACTIVITY_H */
