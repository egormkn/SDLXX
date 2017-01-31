#ifndef SDLXX_SCENETEST_H
#define SDLXX_SCENETEST_H

#include <fstream>
#include "Scene.h"
#include "Texture.h"

namespace SDLXX {
    class SceneTest : public Scene {
    public:

        /*//Screen dimension constants
        static const int SCREEN_WIDTH = 640;
        static const int SCREEN_HEIGHT = 480;

//The dimensions of the level
        static const int LEVEL_WIDTH = 1280;
        static const int LEVEL_HEIGHT = 960;

//Tile constants
        static const int TILE_WIDTH = 80;
        static const int TILE_HEIGHT = 80;
        static const int TOTAL_TILES = 192;
        static const int TOTAL_TILE_SPRITES = 12;


//The different tile sprites
        const int TILE_RED = 0;
        const int TILE_GREEN = 1;
        const int TILE_BLUE = 2;
        static const int TILE_CENTER = 3;
        const int TILE_TOP = 4;
        const int TILE_TOPRIGHT = 5;
        const int TILE_RIGHT = 6;
        const int TILE_BOTTOMRIGHT = 7;
        const int TILE_BOTTOM = 8;
        const int TILE_BOTTOMLEFT = 9;
        const int TILE_LEFT = 10;
        static const int TILE_TOPLEFT = 11;

        SDLXX::Texture gDotTexture;
        SDLXX::Texture gTileTexture;
        SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

        Tile *tileSet[TOTAL_TILES];
        Dot dot;
        SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};*/

        void init(Renderer &renderer) override {
            /*if(!loadMedia(renderer, tileSet)) {
                throw Exception("Failed to load media!");
            }*/
        }

        void cleanUp() override {
            /*for (int i = 0; i < TOTAL_TILES; ++i) {
                if(tileSet[i] != nullptr) {
                    delete tileSet[i];
                    tileSet[i] = nullptr;
                }
            }

            //Free loaded images
            gDotTexture.free();
            gTileTexture.free();*/
        }

        void pause() override {

        }

        void resume() override {

        }

        void handleEvent(SDL_Event &e) override {
            //dot.handleEvent(e);
        }

        void update() override {
            /*dot.move(tileSet);
            dot.setCamera(camera);*/
        }

        void draw(Renderer &renderer) override {
            /*renderer.setColor(Color(0xFFFFFFFF));
            renderer.clear();

            for (int i = 0; i < TOTAL_TILES; ++i) {
                tileSet[i]->render(renderer, camera, this);
            }

            dot.render(renderer, camera);
            renderer.render();*/
        }




//The dot that will move around on the screen




//Scene textures
/*

        bool loadMedia(const SDLXX::Renderer &renderer, Tile *tiles[]) {
            //Loading success flag
            bool success = true;

            //Load dot texture
            if(!gDotTexture.loadFromFile(renderer.getSDLRenderer(), "resources/dot.bmp")) {
                printf("Failed to load dot texture!\n");
                success = false;
            }

            //Load tile texture
            if(!gTileTexture.loadFromFile(renderer.getSDLRenderer(), "resources/tiles.png")) {
                printf("Failed to load tile set texture!\n");
                success = false;
            }

            //Load tile map
            if(!setTiles(tiles)) {
                printf("Failed to load tile set!\n");
                success = false;
            }

            return success;
        }

        static bool checkCollision(SDL_Rect a, SDL_Rect b) {
            //The sides of the rectangles
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;

            //Calculate the sides of rect A
            leftA = a.x;
            rightA = a.x + a.w;
            topA = a.y;
            bottomA = a.y + a.h;

            //Calculate the sides of rect B
            leftB = b.x;
            rightB = b.x + b.w;
            topB = b.y;
            bottomB = b.y + b.h;

            //If any of the sides from A are outside of B
            if(bottomA <= topB) {
                return false;
            }

            if(topA >= bottomB) {
                return false;
            }

            if(rightA <= leftB) {
                return false;
            }

            if(leftA >= rightB) {
                return false;
            }

            //If none of the sides from A are outside B
            return true;
        }

        bool setTiles(Tile *tiles[]) {
            //Success flag
            bool tilesLoaded = true;

            //The tile offsets
            int x = 0, y = 0;

            //Open the map
            std::ifstream map("resources/lazy.map");

            //If the map couldn't be loaded
            if(false) {
                printf("Unable to load map file!\n");
                tilesLoaded = false;
            } else {
                //Initialize the tiles
                for (int i = 0; i < TOTAL_TILES; ++i) {
                    //Determines what kind of tile will be made
                    int tileType = -1;

                    //Read tile from map file
                    map >> tileType;

                    //If the was a problem in reading the map
                    if(map.fail()) {
                        //Stop loading map
                        printf("Error loading map: Unexpected end of file!\n");
                        tilesLoaded = false;
                        break;
                    }

                    //If the number is a valid tile number
                    if((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
                        tiles[i] = new Tile(x, y, tileType);
                    }
                        //If we don't recognize the tile type
                    else {
                        //Stop loading map
                        printf("Error loading map: Invalid tile type at %d!\n", i);
                        tilesLoaded = false;
                        break;
                    }

                    //Move to next tile spot
                    x += TILE_WIDTH;

                    //If we've gone too far
                    if(x >= LEVEL_WIDTH) {
                        //Move back
                        x = 0;

                        //Move to the next row
                        y += TILE_HEIGHT;
                    }
                }

                //Clip the sprite sheet
                if(tilesLoaded) {
                    gTileClips[TILE_RED].x = 0;
                    gTileClips[TILE_RED].y = 0;
                    gTileClips[TILE_RED].w = TILE_WIDTH;
                    gTileClips[TILE_RED].h = TILE_HEIGHT;

                    gTileClips[TILE_GREEN].x = 0;
                    gTileClips[TILE_GREEN].y = 80;
                    gTileClips[TILE_GREEN].w = TILE_WIDTH;
                    gTileClips[TILE_GREEN].h = TILE_HEIGHT;

                    gTileClips[TILE_BLUE].x = 0;
                    gTileClips[TILE_BLUE].y = 160;
                    gTileClips[TILE_BLUE].w = TILE_WIDTH;
                    gTileClips[TILE_BLUE].h = TILE_HEIGHT;

                    gTileClips[TILE_TOPLEFT].x = 80;
                    gTileClips[TILE_TOPLEFT].y = 0;
                    gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
                    gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

                    gTileClips[TILE_LEFT].x = 80;
                    gTileClips[TILE_LEFT].y = 80;
                    gTileClips[TILE_LEFT].w = TILE_WIDTH;
                    gTileClips[TILE_LEFT].h = TILE_HEIGHT;

                    gTileClips[TILE_BOTTOMLEFT].x = 80;
                    gTileClips[TILE_BOTTOMLEFT].y = 160;
                    gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
                    gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

                    gTileClips[TILE_TOP].x = 160;
                    gTileClips[TILE_TOP].y = 0;
                    gTileClips[TILE_TOP].w = TILE_WIDTH;
                    gTileClips[TILE_TOP].h = TILE_HEIGHT;

                    gTileClips[TILE_CENTER].x = 160;
                    gTileClips[TILE_CENTER].y = 80;
                    gTileClips[TILE_CENTER].w = TILE_WIDTH;
                    gTileClips[TILE_CENTER].h = TILE_HEIGHT;

                    gTileClips[TILE_BOTTOM].x = 160;
                    gTileClips[TILE_BOTTOM].y = 160;
                    gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
                    gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

                    gTileClips[TILE_TOPRIGHT].x = 240;
                    gTileClips[TILE_TOPRIGHT].y = 0;
                    gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
                    gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

                    gTileClips[TILE_RIGHT].x = 240;
                    gTileClips[TILE_RIGHT].y = 80;
                    gTileClips[TILE_RIGHT].w = TILE_WIDTH;
                    gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

                    gTileClips[TILE_BOTTOMRIGHT].x = 240;
                    gTileClips[TILE_BOTTOMRIGHT].y = 160;
                    gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
                    gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
                }
            }

            //Close the file
            map.close();

            //If the map was loaded fine
            return tilesLoaded;
        }

        static bool touchesWall(SDL_Rect box, Tile *tiles[]) {
            //Go through the tiles
            for (int i = 0; i < TOTAL_TILES; ++i) {
                //If the tile is a wall type tile
                if((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT)) {
                    //If the collision box touches the wall tile
                    if(checkCollision(box, tiles[i]->getBox())) {
                        return true;
                    }
                }
            }

            //If no wall tiles were touched
            return false;
        }*/


    };
}

#endif // SDLXX_SCENETEST_H
