#ifndef SDLXX_GAME_H
#define SDLXX_GAME_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include "../SDLXX_image.h"
#include "../base/Scene.h"
#include "../base/Texture.h"
#include "Box2DDrawer.h"

#include <Box2D/Box2D.h>

using namespace SDLXX;

const float SCALE = 30.f;
const float DEG = 57.29577f;

class Game : public Scene {
public:

    Game(const std::string &title) : Scene(title) {
        Log::log("[" + getTitle() + "] Scene constructed");
    }

    ~Game() {
        Log::log("[" + getTitle() + "] Scene destructed");
    }

    void setWall(int x, int y, int w, int h) {
        b2PolygonShape groundBox;
        groundBox.SetAsBox(w/SCALE, h/SCALE);

        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(x/SCALE, y/SCALE);
        b2Body *groundBody = world->CreateBody(&groundBodyDef);
        groundBody->CreateFixture(&groundBox, 1);
    }

    void onCreate(Window &w) override {
        Log::log("[" + getTitle() + "] Scene created");
        window = &w;

        b2Vec2 gravity(0.0f, 9.8f);
        world = std::make_unique<b2World>(gravity);
        drawer = new Box2DDrawer(window->getSDLRenderer(), 30.f);
        drawer->SetFlags(0xFF);
        world->SetDebugDraw(drawer);

        setWall(400, 490, 2000, 10);
        setWall(55, 438, 64, 60);
        setWall(710, 435, 100, 60);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(30/SCALE, 30/SCALE);

        // Define the dynamic body. We set its position and call the body factory.
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(600/SCALE, 100/SCALE);
        body = world->CreateBody(&bodyDef);

        body->CreateFixture(&dynamicBox, 2);
        body->SetUserData(&boxName);

        image = new Texture("resources/Downloads/Level/Objects/Box.png", w.getSDLRenderer());
    }

    void onDestroy() override {
        Log::log("[" + getTitle() + "] Scene destroyed");
        // Free resources


        /*delete world;
        world = nullptr;

        delete groundBodyDef;
        groundBodyDef = nullptr;

        delete groundBox;
        delete bodyDef;
        delete dynamicBox;
        delete fixtureDef;

        delete gravity;
        gravity = nullptr;*/

        delete drawer;
        delete image;
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
            if(e.getEvent().key.keysym.sym == SDLK_ESCAPE) {
                finish();
            } else if(e.getEvent().key.keysym.sym == SDLK_UP) {
                for(b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
                    if (it->GetUserData() == &boxName) {
                        it->ApplyLinearImpulse(b2Vec2(0.f, -1000/SCALE), body->GetWorldCenter(), true);
                    }
                }
            } else if(e.getEvent().key.keysym.sym == SDLK_RIGHT) {
                if(e.getEvent().key.repeat == 0) {
                    for(b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
                        if (it->GetUserData() == &boxName) {
                            it->ApplyLinearImpulse(b2Vec2(1000/SCALE, 0.f), body->GetWorldCenter(), true);
                        }
                    }
                }
            } else if(e.getEvent().key.keysym.sym == SDLK_LEFT) {
                if(e.getEvent().key.repeat == 0) {
                    for(b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
                        if (it->GetUserData() == &boxName) {
                            it->ApplyLinearImpulse(b2Vec2(-1000/SCALE, 0.f), body->GetWorldCenter(), true);
                        }
                    }
                }
            }
        }
    }

    void update(Uint32 t, Uint32 dt) override {
        world->Step(((float32) dt) / 1000.0f, 6, 2);
    }

    void render(Renderer &renderer) override {
        renderer.setColor(Color(0xFFFFFFFF));
        renderer.clear();

        for(b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
            if (it->GetUserData() == &boxName) {
                b2Vec2 pos = it->GetPosition();
                float  angle = it->GetAngle();
                image->render(renderer.getSDLRenderer(), (int) (pos.x * SCALE), (int) (pos.y * SCALE), nullptr, angle * DEG);
            } else {

                /*b2Vec2 position = it->GetPosition();

                SDL_Rect fillRect = {
                        (int) (position.x * SCALE), (int) (position.y * SCALE), 100, 100
                };

                renderer.setColor(Color(0xFF8888FF));
                renderer.fillRect(&fillRect);*/
            }
        }

        world->DrawDebugData();
        /**/
        renderer.render();
    }

private:
    int pos = 0;
    Window *window = nullptr;

    std::unique_ptr<b2World> world;
    b2Body *body = nullptr;
    std::string boxName = "box";

    b2Draw *drawer = nullptr;
    Texture *image = nullptr;
};

#endif // SDLXX_GAME_H
