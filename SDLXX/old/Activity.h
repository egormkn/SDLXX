#pragma once
#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_log.h>
#include "GameConstants.h"

class Activity {
public:
    Activity(const std::string &title, SDL_Window *window, SDL_Renderer *renderer) : title(title), pWindow(window),
                                                                                       pRenderer(renderer) {
        SDL_Log("Running activity: %s", title.c_str());
        SDL_SetWindowTitle(pWindow, (gameTitle + " - " + title).c_str());
        SDL_SetRenderDrawColor(pRenderer, 0x00, 0x00, 0x00, 0xFF);
    }

    virtual void render() {
        if (!active) {
            return;
        }
        SDL_RenderClear(pRenderer);
        SDL_RenderPresent(pRenderer);
        SDL_UpdateWindowSurface(pWindow);
    }

    virtual void handleEvent(SDL_Event &e) {
        if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_UP) {
                runIntent(new Activity(title + " test", pWindow, pRenderer));
            } else {
                setActive(false);
            }
        }
    }

    virtual void pause() {
        paused = true;
    }

    virtual void resume() {
        SDL_SetWindowTitle(pWindow, (gameTitle + " - " + title).c_str());
        paused = false;
    }

    bool isActive() {
        return active;
    }

    void setActive(bool value) {
        active = value;
    }

    bool hasIntent() {
        return intent != nullptr;
    }

    void runIntent(Activity *newIntent) {
        if (intent != nullptr) {
            delete intent;
        }
        intent = newIntent;
    }

    Activity *getIntent() {
        Activity *runner = intent;
        intent = nullptr;
        return runner;
    }

    virtual ~Activity() {
        SDL_Log("Closing activity: %s", title.c_str());
        delete intent;
    }

protected:
    SDL_Window *pWindow = NULL;
    SDL_Renderer *pRenderer = NULL;

private:
    std::string title;
    bool active = true, paused = false;
    Activity *intent = nullptr;

};

#endif /* ACTIVITY_H */
