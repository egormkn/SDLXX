#ifndef SDLXX_GAME_H
#define SDLXX_GAME_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include "../SDLXX_image.h"
#include "../base/Scene.h"
#include "../base/Texture.h"
#include "Box2DDrawer.h"
#include "../tmx/TMX_map.h"
#include "../tmx/TMX_map.h"

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

    void setStaticBox(int x, int y, int w, int h) {
        b2PolygonShape groundBox;
        groundBox.SetAsBox(w / SCALE, h / SCALE);

        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(x / SCALE, y / SCALE);
        b2Body *groundBody = world->CreateBody(&groundBodyDef);
        groundBody->CreateFixture(&groundBox, 1);
        groundBody->SetUserData(&staticBoxName);
    }

    void onCreate(Window &w) override {
        Log::log("[" + getTitle() + "] Scene created");
        window = &w;

        b2Vec2 gravity(0.0f, 9.8f);
        world = std::make_unique<b2World>(gravity);
        drawer = new Box2DDrawer(window->getSDLRenderer(), 30.f);
        drawer->SetFlags(0xFF);
        //world->SetDebugDraw(drawer);

        map = new TMX_map();
        map->init("resources/level.tmx");
        MAP_HEIGHT = map->tmx_layers[0].height * 60;
        MAP_WIDTH = map->tmx_layers[0].width * 60;

        //default camera position
        camera = {0, 0};


        std::vector<std::vector<int>> vec = map->tmx_layers[0].tmx_data.data;
        for (int i = 0; i < vec.size(); ++i) {
            for (int j = 0; j < vec[i].size(); ++j) {
                if (vec[i][j] != 0) {
                    setStaticBox(j * 60, i * 60, 30, 30);
                }
            }
        }

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(30 / SCALE, 30 / SCALE);

        // Define the dynamic body. We set its position and call the body factory.
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(600 / SCALE, 100 / SCALE);
        body = world->CreateBody(&bodyDef);

        body->CreateFixture(&dynamicBox, 2);
        body->SetUserData(&boxName);



        /* Circle */
        /*b2CircleShape circleShape;
        circleShape.m_radius = 100 / SCALE;
        b2BodyDef bodyDef2;
        bodyDef2.type = b2_dynamicBody;
        bodyDef2.position.Set(400 / SCALE, 100 / SCALE);
        b2Body *circleBody = world->CreateBody(&bodyDef2);

        circleBody->CreateFixture(&circleShape, 2);*/


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
        delete map;
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
        if (e.getType() == SDL_KEYDOWN) {
            if (e.getEvent().key.keysym.sym == SDLK_ESCAPE) {
                finish();
            } else if (e.getEvent().key.keysym.sym == SDLK_UP) {
                for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
                    if (it->GetUserData() == &boxName) {
                        it->ApplyLinearImpulse(b2Vec2(0.f, -1000 / SCALE), body->GetWorldCenter(), true);
                    }
                }
            } else if (e.getEvent().key.keysym.sym == SDLK_RIGHT) {
                if (e.getEvent().key.repeat == 0) {
                    for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
                        if (it->GetUserData() == &boxName) {
                            it->ApplyLinearImpulse(b2Vec2(1000 / SCALE, 0.f), body->GetWorldCenter(), true);
                        }
                    }
                }
            } else if (e.getEvent().key.keysym.sym == SDLK_LEFT) {
                if (e.getEvent().key.repeat == 0) {
                    for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
                        if (it->GetUserData() == &boxName) {
                            it->ApplyLinearImpulse(b2Vec2(-1000 / SCALE, 0.f), body->GetWorldCenter(), true);
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

        SDL_GetWindowSize(window->getSDLWindow(), &SCREEN_WIDTH, &SCREEN_HEIGHT);
        window->setTitle(std::to_string(SCREEN_WIDTH) + " " + std::to_string(SCREEN_HEIGHT));

        for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
            if (it->GetUserData() == &boxName) {
                camera.x = (int) (it->GetPosition().x * SCALE - SCREEN_WIDTH / 2);
                camera.y = (int) (it->GetPosition().y * SCALE - SCREEN_HEIGHT / 2);
                if (camera.x < -30) {
                    camera.x = -30;
                }
                if (camera.x + SCREEN_WIDTH > MAP_WIDTH - 30) {
                    camera.x = MAP_WIDTH - SCREEN_WIDTH - 30;
                }
                if (camera.y < -30) {
                    camera.y = -30;
                }
                if (camera.y + SCREEN_HEIGHT > MAP_HEIGHT - 30) {
                    camera.y = MAP_HEIGHT - SCREEN_HEIGHT - 30;
                }
            }
        }

        for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
            if (it->GetUserData() == &boxName) {
                renderBox(renderer, it);
            } else if (it->GetUserData() == &staticBoxName) {
                renderBox(renderer, it);
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

    void renderBox(Renderer &renderer, b2Body *boxBody) {
        b2Vec2 pos = boxBody->GetPosition();
        float angle = boxBody->GetAngle();
        const b2PolygonShape *shape = (b2PolygonShape *) boxBody->GetFixtureList()->GetShape();
        b2Vec2 local_vec = shape->m_vertices[0];
        int height = (int) (shape->m_vertices[2].y * 2 * SCALE);
        int width = (int) (shape->m_vertices[2].x * 2 * SCALE);
        SDL_Rect renderQuad = {(int) ((pos.x + local_vec.x) * SCALE - camera.x),
                               (int) ((pos.y + local_vec.y) * SCALE - camera.y), height,
                               width};


        SDL_Point point = {(int) (shape->m_vertices[2].x * SCALE), (int) (shape->m_vertices[2].y * SCALE)};
        image->render(renderer.getSDLRenderer(), nullptr, &renderQuad, angle * DEG, &point);
    }

private:
    int pos = 0;
    Window *window = nullptr;

    std::unique_ptr<b2World> world;
    b2Body *body = nullptr;
    std::string boxName = "box";
    std::string staticBoxName = "static_box";

    b2Draw *drawer = nullptr;
    Texture *image = nullptr;

    SDL_Point camera;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int MAP_WIDTH;
    int MAP_HEIGHT;

    TMX_map *map;
};

#endif // SDLXX_GAME_H
