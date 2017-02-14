#ifndef SDLXX_TMX_MAP_H
#define SDLXX_TMX_MAP_H

#include <iostream>
#include "../../tinyxml2/tinyxml2.h"
#include "TMX_tileset.h"
#include "TMX_Utils.h"
#include "TMX_layer.h"
#include <vector>

class TMX_map {
private:
    const tinyxml2::XMLElement *map;

public:
    double version;
    TMX::Orientation orientation;
    TMX::RenderOrder renderOrder;
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    int hexSideLength;
    TMX::StaggerAxis staggerAxis;
    TMX::StaggerIndex staggerIndex;
    std::string backgroundColor;
    int nextObjectID;

    TMX_tileset tmx_tileset;
    std::vector<TMX_layer>  tmx_layers;

    TMX_map();

    void init(const tinyxml2::XMLElement *map_);

    /*void show() {
        std::cout << "version: " << version << '\n';
        std::cout << "orientation: " << orientation << '\n';
        std::cout << "renderOrder: " << renderOrder << '\n';
        std::cout << "width: " << width << '\n';
        std::cout << "height: " << height << '\n';
        std::cout << "tileWidth: " << tileWidth << '\n';
        std::cout << "tileHeight: " << tileHeight << '\n';
        std::cout << "hexSideLength: " << hexSideLength << '\n';
        std::cout << "staggerAxis: " << staggerAxis << '\n';
        std::cout << "staggerIndex: " << staggerIndex << '\n';
        std::cout << "backgroundColor: " << backgroundColor << '\n';
        std::cout << "nextObjectID: " << nextObjectID << '\n';
    }*/
};


#endif //SDLXX_TMX_MAP_H
