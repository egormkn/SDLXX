#ifndef SDLXX_TMX_TILESET_H
#define SDLXX_TMX_TILESET_H

#include <string>
#include "tinyxml2.h"
#include "TMX_Utils.h"
#include "TMX_image.h"
#include "TMX_tile.h"
#include <vector>

class TMX_tileset {
public:
    int firstgid;
    std::string source;
    std::string name;
    int tilewidth;
    int tileheight;
    int spacing;
    int margin;
    int tilecount;
    int columns;

    TMX_image tmx_image;
    std::vector<TMX_tile> tmx_tiles;

    TMX_tileset();


    void init(const tinyxml2::XMLElement *element);
};


#endif //SDLXX_TMX_TILESET_H
