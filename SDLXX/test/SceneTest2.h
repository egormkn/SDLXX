#ifndef SDLXX_SCENETEST2_H
#define SDLXX_SCENETEST2_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include "../base/Scene.h"
#include "../base/Texture.h"
#include "../physics/Object.h"
#include "SceneTest.h"

namespace SDLXX {
    class SceneTest2 : public Scene {
    public:

        void init(Window &window) override {
            setActive(true);
        }

        void cleanUp() override {

        }

        void pause() override {

        }

        void resume() override {

        }

        void handleEvent(Event &e) override {
            if(e.getType() == SDL_KEYDOWN) {
                if(e.getEvent().key.keysym.sym == SDLK_UP) {
                    //runIntent(new SceneTest);
                } else {
                    setActive(false);
                }
            }
        }

        void update() override {
            pos += 1;
            if (pos > 300) {
                pos = 0;
            }
        }

        void render(Renderer &renderer) override {
            renderer.setColor(Color(0xFFFFFFFF));
            renderer.clear();

            SDL_Rect fillRect = {
                    pos, 10, 100, 100
            };

            renderer.setColor(Color(0xFF8800FF));
            SDL_RenderFillRect(renderer.getSDLRenderer(), &fillRect );
            renderer.render();
        }

    private:
        int pos = 0;

        std::vector<Object *> objects;
    };
}

#endif // SDLXX_SCENETEST2_H
