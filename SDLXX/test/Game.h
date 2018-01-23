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
        std::vector<TMX_object> tmx_objects;

        TextureHolder(Texture *texture, const SDL_Rect &rect, const std::vector<TMX_object> &tmx_objects);
    };

public:

    Game(const std::string &title);

    ~Game();

    void setStaticBox(int x, int y, float w, float h);

    void onCreate(Window &w) override;

    void onDestroy() override;

    void onPause() override;

    void onResume() override;

    void handleEvent(Event &e) override;

    void update(Uint32 t, Uint32 dt) override;

    void render(Renderer &renderer) override;

    void renderBox(Renderer &renderer, b2Body *boxBody);

    void renderPlayer(Renderer &renderer, b2Body *boxBody);

private:
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
