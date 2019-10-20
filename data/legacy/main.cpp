#include <stack>
#include <SDL.h>
#include <SDL_image.h>
//*#include <SDL_mixer.h>*/
//*#include <SDL_net.h>*/
//*#include <SDL_ttf.h>*/

#include "SDL/SDLException.h"
#include "GameConstants.h"
#include "GameMenuActivity.h"

struct State {
    float x;
    float v;
};

struct Derivative {
    float dx;
    float dv;
};

void initSDL(SDL_Window *&pWindow, SDL_Renderer *&pRenderer) {

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw SDLException("SDL could not initialize", SDL_GetError());
    }

    SDL_Log("SDL initialized");

    // Get current display mode of all displays.
    SDL_DisplayMode current;
    for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
        if(SDL_GetCurrentDisplayMode(i, &current) != 0) {
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
        } else {
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz", i, current.w, current.h,
                    current.refresh_rate);
        }
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        SDL_Log("Linear texture filtering not enabled!");
    }

    //Create window
    Uint32 windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
    pWindow = SDL_CreateWindow(gameTitle.c_str(),
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               640,
                               480,
                               windowFlags);
    if(pWindow == NULL) {
        throw SDLException("Window could not be created", SDL_GetError());
    }

    //Create renderer for window
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(pRenderer == NULL) {
        pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_SOFTWARE);
        if(pRenderer == NULL) {
            throw SDLException("Renderer could not be created", SDL_GetError());
        }
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        throw SDLException("SDL_image could not initialize", IMG_GetError());
    }
}

void closeSDL(SDL_Window *&pWindow, SDL_Renderer *&pRenderer) {
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    pRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    SDL_Window *gWindow = NULL;
    SDL_Renderer *gRenderer = NULL;
    try {
        initSDL(gWindow, gRenderer);
    } catch (const std::exception &err) {
        SDL_Log("Error while initializing SDL: \n - %s", err.what());
        return 0;
    }


    std::stack<Activity *> activities;
    activities.push(new GameMenuActivity(gWindow, gRenderer));

    while (activities.size() > 0) {
        Activity *currentView = activities.top();
        if(!currentView->isActive()) {
            Activity *intent = nullptr;
            if(currentView->hasIntent()) {
                intent = currentView->getIntent();
            }
            delete currentView;
            activities.pop();
            if(intent != nullptr) {
                activities.push(intent);
            } else if(activities.size() > 0) {
                activities.top()->resume();
            }
            continue;
        }

        if(currentView->hasIntent()) {
            activities.push(currentView->getIntent());
            currentView->pause();
            continue;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                while (activities.size() > 0) {
                    delete activities.top();
                    activities.pop();
                }
            } else {
                currentView->handleEvent(e);
            }
        }

        if (activities.size() > 0) {
            currentView->render();
        }
    }

    // runGame(gWindow, gRenderer);

    closeSDL(gWindow, gRenderer);
    return 0;
}