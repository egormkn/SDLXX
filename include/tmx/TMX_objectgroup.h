#ifndef SDLXX_TMX_OBJECTGROUP_H
#define SDLXX_TMX_OBJECTGROUP_H

#include <vector>
#include "TMX_object.h"
#include "tinyxml2.h"

class TMX_objectgroup {
public:
    std::vector<TMX_object> tmx_objects;

    TMX_objectgroup() {}

    void init(const tinyxml2::XMLElement *element) {
        if (element == NULL) {
            return;
        }
        for (const tinyxml2::XMLElement *e = element->FirstChildElement("object");
             e != NULL; e = e->NextSiblingElement("object")) {
            TMX_object object;
            object.init(e);
            tmx_objects.push_back(object);
        }
    }
};


#endif //SDLXX_TMX_OBJECTGROUP_H
