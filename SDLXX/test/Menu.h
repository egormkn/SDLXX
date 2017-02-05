#ifndef SDLXX_SCENETEST_H
#define SDLXX_SCENETEST_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include <SDLXX/base/Object.h>
#include <SDLXX/gui/Button.h>
#include "../SDLXX_image.h"
#include "../base/Scene.h"
#include "../base/Texture.h"
#include "Game.h"

namespace SDLXX {
    class Menu : public Scene {
    public:

        Menu(const std::string &title) : Scene(title) {
            Log::log("[" + getTitle() + "] Scene constructed");
            Button *exitButton = new Button(-100, -25, 200, 50);
            exitButton->setRelativePosition(50, 50);
            exitButton->setText("Exit");
            objects.resize(1);
            objects[0] = exitButton;
        }

        ~Menu() {
            Log::log("[" + getTitle() + "] Scene destructed");
            delete objects[0];
            objects.clear();
        }

        void onCreate(Window &w) override {
            Log::log("[" + getTitle() + "] Scene created");


            window = &w;
            // Init resources
            // After: setInitialized(true);



            std::string path = "resources/background.jpg";

            //Load image at specified path
            SDL_Surface *loadedSurface = IMG_Load(path.c_str());
            if(loadedSurface == nullptr) {
                printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
            } else {
                //Create texture from surface pixels
                image = SDL_CreateTextureFromSurface(w.getSDLRenderer(), loadedSurface);
                if(image == nullptr) {
                    printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
                }

                //Get rid of old loaded surface
                SDL_FreeSurface(loadedSurface);
            }


        }

        void onDestroy() override {
            Log::log("[" + getTitle() + "] Scene destroyed");
            // Free resources
            SDL_DestroyTexture(image);
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
                    runIntent(new Game("Game"));
                    // finish();
                    // My changes
                } else {
                    finish();
                }
            }
            if(objects[0]->handleEvent(e)) {
                if (e.getType() == SDL_MOUSEBUTTONDOWN) {
                    runIntent(new Game("Game"));
                }
            }
        }

        void update(Uint32 t, Uint32 dt) override {
            Dimensions d = window->getDimensions();

            objects[0]->update(t, dt, d);
        }

        void render(Renderer &renderer) override {
            /*renderer.setColor(Color(0xFFFFFFFF));
            renderer.clear();

            SDL_Rect fillRect = {
                    pos, 10, 100, 100
            };

            renderer.setColor(Color(0xFF8888FF));
            SDL_RenderFillRect(renderer.getSDLRenderer(), &fillRect);
            renderer.render();*/
            SDL_RenderCopy(renderer.getSDLRenderer(), image, NULL, NULL);
            // renderer.renderCopy(Texture(image));
            objects[0]->render(renderer);
            renderer.render();
        }

    private:
        int pos = 0;
        bool loaded = false;
        std::vector<Object *> objects;
        SDL_Texture *image = nullptr;
        Window *window = nullptr;
    };
}

#endif // SDLXX_SCENETEST_H
