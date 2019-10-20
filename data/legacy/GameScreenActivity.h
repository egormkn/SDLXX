#pragma once
#ifndef GAMESCREENACTIVITY_H
#define GAMESCREENACTIVITY_H

#include "Activity.h"

class GameScreenActivity : public Activity {
public:
    GameScreenActivity(SDL_Window *gWindow, SDL_Renderer *gRenderer) : Activity("Game", gWindow, gRenderer) {
        /*if (!loadMedia(tileSet)) {
            SDL_Log("Failed to load media");
            setActive(false);
        }*/
    }

    /*virtual void render() {


        /*int winwidth;
        int winheight;
        SDL_GetWindowSize(pWindow, &winwidth, &winheight);

        //map camera
        SDL_Rect camera = {0, 0, winwidth, winheight};

        //Move the dot
        dot.move(tileSet);
        dot.setCamera(camera);

        //Clear screen
        SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(pRenderer);

        //Render level
        for (int i = 0; i < TOTAL_TILES; ++i) {
            tileSet[i]->render(camera);
        }

        //Render dot
        dot.render(camera);

        //Update screen
        SDL_RenderPresent(pRenderer);

    }*/

    virtual void handleEvent(SDL_Event &e) {
        if(e.type == SDL_KEYDOWN) {
            setActive(false);
            return;
        }
        /*dot.handleEvent(e);*/
    }

    ~GameScreenActivity() {
        /*for (int i = 0; i < TOTAL_TILES; ++i) {
            if (tileSet[i] == NULL) {
                delete tileSet[i];
                tileSet[i] = NULL;
            }
        }

        //Free loaded images
        gDotTexture.free();
        gTileTexture.free();*/
    }

};


#endif /* GAMESCREENACTIVITY_H */
