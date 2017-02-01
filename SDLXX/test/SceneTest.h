#ifndef SDLXX_SCENETEST_H
#define SDLXX_SCENETEST_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include "../SDLXX_image.h"
#include "../base/Scene.h"
#include "../base/Texture.h"
#include "../physics/Object.h"

namespace SDLXX {
    class SceneTest : public Scene {
    public:

        SceneTest(const std::string &title) : Scene(title) {
            Log::log("[" + getTitle() + "] Scene constructed");
        }

        ~SceneTest() {
            Log::log("[" + getTitle() + "] Scene destructed");
        }

        void onCreate(Window &window) override {
            Log::log("[" + getTitle() + "] Scene created");
            // Init resources
            // After: setInitialized(true);
            screen = SDL_GetWindowSurface(window.getSDLWindow());


            //Load image at specified path
            SDL_Surface *loadedSurface = IMG_Load("resources/background.jpg");
            if(loadedSurface == NULL) {
                printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
            } else {
                //Convert surface to screen format
                image = SDL_ConvertSurface(loadedSurface, screen->format, NULL);
                if(image == NULL) {
                    printf("Unable to optimize image! SDL Error: %s\n", SDL_GetError());
                }

                //Get rid of old loaded surface
                SDL_FreeSurface(loadedSurface);
            }


        }

        void onDestroy() override {
            Log::log("[" + getTitle() + "] Scene destroyed");
            // Free resources
            SDL_FreeSurface( image );
            image = nullptr;
        }

        void onPause() override {
            // Save state
            // After: setPaused(true);
        }

        void onResume() override {
            // Restore state
            // After: setPaused(false);
        }

        void handleEvent(Event &e) override {
            if(e.getType() == SDL_KEYDOWN) {
                if(e.getEvent().key.keysym.sym == SDLK_UP) {
                    Log::log("[" + getTitle() + "] UP");
                    runIntent(new SceneTest("New title"));
                    // finish();
                } else {
                    finish();
                }
            }
        }

        void update(Uint32 t, Uint32 dt) override {
            pos += 1;
            if(pos > 300) {
                pos = 0;
            }
        }

        void render(Window &window) override {
            /*renderer.setColor(Color(0xFFFFFFFF));
            renderer.clear();

            SDL_Rect fillRect = {
                    pos, 10, 100, 100
            };

            renderer.setColor(Color(0xFF8888FF));
            SDL_RenderFillRect(renderer.getSDLRenderer(), &fillRect);
            renderer.render();*/
            SDL_BlitSurface( image, NULL, screen, NULL );

            //Update the surface
            SDL_UpdateWindowSurface( window.getSDLWindow() );
        }

    private:
        int pos = 0;
        bool loaded = false;
        std::vector<Object *> objects;
        SDL_Surface *screen = nullptr, *image = nullptr;
    };
}

#endif // SDLXX_SCENETEST_H
