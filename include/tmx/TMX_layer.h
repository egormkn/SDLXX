#ifndef SDLXX_TMX_LAYER_H
#define SDLXX_TMX_LAYER_H

#include "tinyxml2.h"
#include "TMX_Utils.h"
#include "TMX_data.h"
#include <string>

class TMX_layer {
public:
    std::string name;
    int x;
    int y;
    int width;
    int height;
    double opacity;
    double visible;
    int offsetsx;
    int offsety;

    TMX_data tmx_data;

    TMX_layer();

    void init(const tinyxml2::XMLElement *element);
};


#endif //SDLXX_TMX_LAYER_H
