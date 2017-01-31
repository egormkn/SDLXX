#ifndef SDLXX_TILE_H
#define SDLXX_TILE_H

#include "Renderer.h"
#include "Scene.h"
#include "SceneTest.h"

namespace SDLXX {
    class SceneTest;

    class Tile {
    public:
        //Initializes position and type
        Tile(int x, int y, int tileType);

        //Shows the tile
        void render(const SDLXX::Renderer &renderer, SDL_Rect &camera, SceneTest *scene);

        //Get the tile type
        int getType();

        //Get the collision box
        SDL_Rect getBox();

    private:
        //The attributes of the tile
        SDL_Rect mBox;

        //The tile type
        int mType;
    };
}

#endif // SDLXX_TILE_H
