#ifndef SDLXX_TMX_OFFSET_H
#define SDLXX_TMX_OFFSET_H

#include "tinyxml2.h"
#include "TMX_Utils.h"

class TMX_offset {
public:
    int x;
    int y;

    TMX_offset();

    void init(const tinyxml2::XMLElement *element);
};


#endif //SDLXX_TMX_OFFSET_H
