#ifndef SDLXX_TMX_TILE_H
#define SDLXX_TMX_TILE_H

#include "TMX_image.h"

class TMX_tile {
public:
    int id;
    TMX_image tmx_image;

    TMX_tile();

    void init(const tinyxml2::XMLElement *element);
};


#endif //SDLXX_TMX_TILE_H
