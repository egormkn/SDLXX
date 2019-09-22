#ifndef SDLXX_GAME_H
#define SDLXX_GAME_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include <sdlxx/image/SDLXX_image.h>
#include <sdlxx/core/Scene.h>
#include <sdlxx/core/Texture.h>
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
        std::vector<TMX_object> tmx_objects;

        TextureHolder(Texture *texture, const SDL_Rect &rect, const std::vector<TMX_object> &tmx_objects);
    };

public:

    Game(const std::string &title);

    ~Game();

    void setStaticBox(int x, int y, float w, float h);

/*        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set((x + w) / SCALE, (y + h) / SCALE);
        b2Body *groundBody = world->CreateBody(&groundBodyDef);
        groundBody->CreateFixture(&groundBox, 1);
        //groundBody->SetUserData(&staticBoxName);
    }*/

    void onCreate(Window &w) override;

    void onDestroy() override;

        /*b2Vec2 gravity(0.0f, 9.8f);
        world = std::make_unique<b2World>(gravity);
        drawer = new Box2DDrawer(window->getSDLRenderer(), 30.f);
        drawer->SetFlags(0xFF);
        //world->SetDebugDraw(drawer);*/

    void onPause() override;

    void onResume() override;

        /*for (std::vector<TMX_tileset>::const_iterator tileset = map2->tmx_tilesets.begin();
             tileset != map2->tmx_tilesets.end(); ++tileset) {
            if (!tileset->tmx_image.source.empty()) {
                int raw = tileset->tilecount / tileset->columns;
                textures.push_back(new Texture(tileset->tmx_image.source, w.getSDLRenderer(), tileset->tilewidth,
                                               tileset->tileheight));
                std::vector<TMX_tile>::const_iterator tile = tileset->tmx_tiles.begin();
                for (int i = 0; i < raw; ++i) {
                    for (int j = 0; j < tileset->columns; ++j) {
                        if (tile->id == i * tileset->columns + j) {
                            textureHolders.push_back(TextureHolder(textures[textures.size() - 1],
                                                                   {j * tileset->tilewidth, i * tileset->tileheight,
                                                                    tileset->tilewidth, tileset->tileheight},
                                                                   tile->tmx_objectgroup.tmx_objects));
                            ++tile;
                        } else {
                            textureHolders.push_back(TextureHolder(textures[textures.size() - 1],
                                                                   {j * tileset->tilewidth, i * tileset->tileheight,
                                                                    tileset->tilewidth, tileset->tileheight},
                                                                   std::vector<TMX_object>()));
                        }
                    }
                }
            } else {
                for (std::vector<TMX_tile>::const_iterator tile = tileset->tmx_tiles.begin();
                     tile != tileset->tmx_tiles.end(); ++tile) {
                    textures.push_back(new Texture(tile->tmx_image.source, w.getSDLRenderer(), tile->tmx_image.width,
                                                   tile->tmx_image.height));
                    textureHolders.push_back(
                            TextureHolder(textures[textures.size() - 1], {0, 0, tile->width, tile->height},
                                          tile->tmx_objectgroup.tmx_objects));
                }
            }
        }*/

    void handleEvent(Event &e) override;

    void update(Uint32 t, Uint32 dt) override;

    void render(Renderer &renderer) override;

    void renderBox(Renderer &renderer, b2Body *boxBody);


        /*for (std::vector<TMX_layer>::const_iterator tmx_layers = map2->tmx_layers.begin();
             tmx_layers != map2->tmx_layers.end(); ++tmx_layers) {
            std::vector<std::vector<int>> vector = tmx_layers->tmx_data.data;
            for (int i = 0; i < vector.size(); ++i) {
                for (int j = 0; j < vector[i].size(); ++j) {
                    if (vector[i][j] != 0) {
                        for (std::vector<TMX_object>::const_iterator object = textureHolders[vector[i][j] -
                                                                                             1].tmx_objects.begin();
                             object != textureHolders[vector[i][j] - 1].tmx_objects.end(); ++object) {
                            setStaticBox(j * TILE_WIDTH + object->x, i * TILE_HEIGHT + object->y,
                                         ((float) object->width) / 2,
                                         ((float) object->height) / 2);
                        }
                    }
                }
            }
        }

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(TILE_WIDTH / 2 / SCALE, TILE_HEIGHT / 2 / SCALE);

        // Define the dynamic body. We set its position and call the body factory.
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(600 / SCALE, 100 / SCALE);
        body = world->CreateBody(&bodyDef);

        body->CreateFixture(&dynamicBox, 2);
        body->SetUserData(&boxName);



        b2CircleShape circleShape;
        circleShape.m_radius = 100 / SCALE;
        b2BodyDef bodyDef2;
        bodyDef2.type = b2_dynamicBody;
        bodyDef2.position.Set(400 / SCALE, 100 / SCALE);
        b2Body *circleBody = world->CreateBody(&bodyDef2);

        circleBody->CreateFixture(&circleShape, 2);


        image = new Texture("resources/Downloads/Level/Objects/Box.png", w.getSDLRenderer(), TILE_WIDTH,
                            TILE_HEIGHT);
    }

    void onDestroy() override {
        Log::log("[" + getTitle() + "] Scene destroyed");
        // Free resources


        delete world;
        world = nullptr;

        delete groundBodyDef;
        groundBodyDef = nullptr;

        delete groundBox;
        delete bodyDef;
        delete dynamicBox;
        delete fixtureDef;

        delete gravity;
        gravity = nullptr;

        for (std::vector<Texture *>::iterator iterator = textures.begin(); iterator != textures.end(); ++iterator) {
            delete *iterator;
        }
        delete drawer;
        delete image;
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
                window->setTitle(std::to_string(it->GetPosition().x * SCALE) + " " +
                                 std::to_string(it->GetPosition().y * SCALE));
                camera.x = (int) (it->GetPosition().x * SCALE - SCREEN_WIDTH / 2);
                camera.y = (int) (it->GetPosition().y * SCALE - SCREEN_HEIGHT / 2);
                if (camera.x < 0) {
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
        //window->setTitle(std::to_string(camera.x) + " " + std::to_string(camera.y));


        for (std::vector<TMX_layer>::const_iterator tmx_layers = map2->tmx_layers.begin();
             tmx_layers != map2->tmx_layers.end(); ++tmx_layers) {
            std::vector<std::vector<int>> vec = tmx_layers->tmx_data.data;
            for (int i = 0; i < vec.size(); ++i) {
                for (int j = 0; j < vec[i].size(); ++j) {
                    if (vec[i][j] != 0) {
                        SDL_Rect rect = {j * TILE_WIDTH - camera.x, i * TILE_HEIGHT - camera.y, TILE_WIDTH,
                                         TILE_HEIGHT};
                        textureHolders[vec[i][j] - 1].texture->render(renderer.getSDLRenderer(),
                                                                      &textureHolders[vec[i][j] - 1].rect, &rect);
                    }
                }
            }
        }

        for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext()) {
            if (it->GetUserData() == &boxName) {
                renderBox(renderer, it);
            } else if (it->GetUserData() == &staticBoxName) {
                renderBox(renderer, it);
                b2Vec2 position = it->GetPosition();

                SDL_Rect fillRect = {
                        (int) (position.x * SCALE), (int) (position.y * SCALE), 100, 100
                };

                renderer.setColor(Color(0xFF8888FF));
                renderer.fillRect(&fillRect);
            }
        }

        world->DrawDebugData();

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
                               (int) ((pos.y + local_vec.y) * SCALE - camera.y),
                               height,
                               width};


        //SDL_Point point = {(int) shape->m_vertices[2].x, (int) shape->m_vertices[2].y};
        image->render(renderer.getSDLRenderer(), nullptr, &renderQuad, angle * DEG);
    }
*/

  void renderPlayer(Renderer &renderer, b2Body *boxBody);

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
    int TILE_WIDTH;
    int TILE_HEIGHT;

    TMX_map *map2;
};

#endif // SDLXX_GAME_H
