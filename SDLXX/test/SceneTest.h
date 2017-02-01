#ifndef SDLXX_SCENETEST_H
#define SDLXX_SCENETEST_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
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
        }

        void onDestroy() override {
            Log::log("[" + getTitle() + "] Scene destroyed");
            // Free resources
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

        void render(Renderer &renderer) override {
            renderer.setColor(Color(0xFFFFFFFF));
            renderer.clear();

            SDL_Rect fillRect = {
                    pos, 10, 100, 100
            };

            renderer.setColor(Color(0xFF8888FF));
            SDL_RenderFillRect(renderer.getSDLRenderer(), &fillRect);
            renderer.render();
        }

    private:
        int pos = 0;
        std::vector<Object *> objects;
    };
}

#endif // SDLXX_SCENETEST_H
