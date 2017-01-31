#ifndef SDLXX_DOT_H
#define SDLXX_DOT_H

#include <SDL_events.h>
#include "Tile.h"

namespace SDLXX {
    class Dot {
    public:
        //The dimensions of the dot
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;

        //Maximum axis velocity of the dot
        static const int DOT_VEL = 10;

        //Initializes the variables
        Dot();

        //Takes key presses and adjusts the dot's velocity
        void handleEvent(SDL_Event &e);

        //Moves the dot and check collision against tiles
        void move(Tile *tiles[]);

        //Centers the camera over the dot
        void setCamera(SDL_Rect &camera);

        //Shows the dot on the screen
        void render(const SDLXX::Renderer &renderer, SDL_Rect &camera);

    private:
        //Collision box of the dot
        SDL_Rect mBox;

        //The velocity of the dot
        int mVelX, mVelY;
    };
}

#endif //SDLXX_DOT_H
