#ifndef SDLXX_TMX_TILE_H
#define SDLXX_TMX_TILE_H

#include "TMX_image.h"
#include "TMX_objectgroup.h"

class TMX_tile {
public:
    int id;
    int width;
    int height;
    TMX_image tmx_image;
    TMX_objectgroup tmx_objectgroup;

    TMX_tile();

    void init(const tinyxml2::XMLElement *element);
};


#endif //SDLXX_TMX_TILE_H
