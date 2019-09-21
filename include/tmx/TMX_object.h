#ifndef SDLXX_TMX_OBJECT_H
#define SDLXX_TMX_OBJECT_H

#include "tinyxml2.h"
#include "TMX_Utils.h"

class TMX_object {
public:
    int id;
    int x;
    int y;
    int width;
    int height;

    TMX_object() {
        id = 0;
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }

    void init(const tinyxml2::XMLElement *element) {
        if (element == NULL) {
            return;
        }
        id = TMX_Utils::getAttributeInt(element, "id");
        x = TMX_Utils::getAttributeInt(element, "x");
        y = TMX_Utils::getAttributeInt(element, "y");
        width = TMX_Utils::getAttributeInt(element, "width");
        height = TMX_Utils::getAttributeInt(element, "height");
    }
};


#endif //SDLXX_TMX_OBJECT_H
