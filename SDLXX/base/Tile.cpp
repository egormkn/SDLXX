#include "Tile.h"

SDLXX::Tile::Tile(int x, int y, int tileType) {
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = 80;
    mBox.h = 80;

    //Get the tile type
    mType = tileType;
}

void SDLXX::Tile::render(const SDLXX::Renderer &renderer, SDL_Rect &camera, SceneTest *scene) {
    //If the tile is on screen
    if(scene->checkCollision(camera, mBox)) {
        //Show the tile
        scene->gTileTexture.render(renderer.getSDLRenderer(), mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
    }
}

int SDLXX::Tile::getType() {
    return mType;
}

SDL_Rect SDLXX::Tile::getBox() {
    return mBox;
}