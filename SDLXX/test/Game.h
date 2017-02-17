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
private:
    struct TextureHolder {
        Texture *texture;
        SDL_Rect rect;
    };
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
        DEFAULT_BOX_SIZE = 64;
        MAP_HEIGHT = map->tmx_layers[0].height * DEFAULT_BOX_SIZE;
        MAP_WIDTH = map->tmx_layers[0].width * DEFAULT_BOX_SIZE;


        map2 = new TMX_map();
        map2->init("resources/level2.tmx");

        for (std::vector<TMX_tileset>::const_iterator tileset = map2->tmx_tilesets.begin();
             tileset != map2->tmx_tilesets.end(); ++tileset) {
            if (!tileset->tmx_image.source.empty()) {
                int raw = tileset->tilecount / tileset->columns;
                int width = DEFAULT_BOX_SIZE * tileset->columns;
                int height = DEFAULT_BOX_SIZE * raw;
                textures.push_back(new Texture(tileset->tmx_image.source, w.getSDLRenderer(), width, height));
                for (int i = 0; i < raw; ++i) {
                    for (int j = 0; j < tileset->columns; ++j) {
                        textureHolders.push_back(
                                {textures[textures.size() - 1],
                                 {j * DEFAULT_BOX_SIZE, i * DEFAULT_BOX_SIZE, DEFAULT_BOX_SIZE, DEFAULT_BOX_SIZE}});
                    }
                }
            } else {
                for (std::vector<TMX_tile>::const_iterator tile = tileset->tiles.begin();
                     tile != tileset->tiles.end(); ++tile) {
                    textures.push_back(new Texture(tile->tmx_image.source, w.getSDLRenderer(), DEFAULT_BOX_SIZE,
                                                   DEFAULT_BOX_SIZE));
                    textureHolders.push_back(
                            {textures[textures.size() - 1], {0, 0, DEFAULT_BOX_SIZE, DEFAULT_BOX_SIZE}});
                }
            }
        }

        //default camera position
        camera = {0, 0};


        std::vector<std::vector<int>> vec = map->tmx_layers[0].tmx_data.data;
        for (int i = 0; i < vec.size(); ++i) {
            for (int j = 0; j < vec[i].size(); ++j) {
                if (vec[i][j] != 0) {
                    setStaticBox(j * DEFAULT_BOX_SIZE, i * DEFAULT_BOX_SIZE, DEFAULT_BOX_SIZE / 2,
                                 DEFAULT_BOX_SIZE / 2);
                }
            }
        }

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(DEFAULT_BOX_SIZE / 2 / SCALE, DEFAULT_BOX_SIZE / 2 / SCALE);

        // Define the dynamic body. We set its position and call the body factory.
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(600 / SCALE, 100 / SCALE);
        body = world->CreateBody(&bodyDef);

        body->CreateFixture(&dynamicBox, 0.8);
        body->SetUserData(&boxName);



        /* Circle */
        /*b2CircleShape circleShape;
        circleShape.m_radius = 100 / SCALE;
        b2BodyDef bodyDef2;
        bodyDef2.type = b2_dynamicBody;
        bodyDef2.position.Set(400 / SCALE, 100 / SCALE);
        b2Body *circleBody = world->CreateBody(&bodyDef2);

        circleBody->CreateFixture(&circleShape, 2);*/


        image = new Texture("resources/Downloads/Level/Objects/Box.png", w.getSDLRenderer(), DEFAULT_BOX_SIZE,
                            DEFAULT_BOX_SIZE);
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

        for (std::vector<Texture *>::iterator iterator = textures.begin(); iterator != textures.end(); ++iterator) {
            delete *iterator;
        }
        delete drawer;
        delete image;
        delete map;
        delete map2;
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
                if (e.getEvent().key.repeat == 0) {
                    for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
                        if(it->GetUserData() == &boxName) {
                            it->ApplyLinearImpulse(b2Vec2(0.f, -1000 / SCALE), body->GetWorldCenter(), true);
                        }
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
            } else if (e.getEvent().key.keysym.sym == SDLK_DOWN) {
                if (e.getEvent().key.repeat == 0) {
                    for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
                        if (it->GetUserData() == &boxName) {
                            it->ApplyLinearImpulse(b2Vec2(0.f, 1000 / SCALE), body->GetWorldCenter(), true);
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
                //window->setTitle(std::to_string(it->GetPosition().x * SCALE) + " " + std::to_string(it->GetPosition().y * SCALE));
                camera.x = (int) (it->GetPosition().x * SCALE - SCREEN_WIDTH / 2);
                camera.y = (int) (it->GetPosition().y * SCALE - SCREEN_HEIGHT/ 2);
                if (camera.x <  0) {
                    camera.x = 0;
                }
                if (camera.x + SCREEN_WIDTH > MAP_WIDTH) {
                    camera.x = MAP_WIDTH - SCREEN_WIDTH;
                }
                if (camera.y < 0) {
                    camera.y = 0;
                }
                if (camera.y + SCREEN_HEIGHT > MAP_HEIGHT) {
                    camera.y = MAP_HEIGHT - SCREEN_HEIGHT;
                }
            }
        }
        window->setTitle(std::to_string(camera.x) + " " + std::to_string(camera.y));


        std::vector<std::vector<int>> vec = map2->tmx_layers[0].tmx_data.data;
        for (int i = 0; i < vec.size(); ++i) {
            for (int j = 0; j < vec[i].size(); ++j) {
                if (vec[i][j] != 0) {
                    SDL_Rect rect = {j * DEFAULT_BOX_SIZE - camera.x, i * DEFAULT_BOX_SIZE - camera.y, DEFAULT_BOX_SIZE, DEFAULT_BOX_SIZE};
                    textureHolders[vec[i][j] - 1].texture->render(renderer.getSDLRenderer(), &textureHolders[vec[i][j] - 1].rect, &rect);
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
        SDL_Rect renderQuad = {(int) ((pos.x + local_vec.x) * SCALE - camera.x + DEFAULT_BOX_SIZE / 2),
                               (int) ((pos.y + local_vec.y) * SCALE - camera.y + DEFAULT_BOX_SIZE / 2), DEFAULT_BOX_SIZE,
                               DEFAULT_BOX_SIZE};


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
    std::vector<Texture *> textures;
    std::vector<TextureHolder> textureHolders;

    SDL_Point camera;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int MAP_WIDTH;
    int MAP_HEIGHT;
    int DEFAULT_BOX_SIZE;

    TMX_map *map;
    TMX_map *map2;
};

#endif // SDLXX_GAME_H
