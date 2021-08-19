#ifndef SDLXX_TXM_IMAGE_H
#define SDLXX_TXM_IMAGE_H

#include "tinyxml2.h"
#include "TMX_Utils.h"
#include <string>

class TMX_image {
public:
    std::string format;
    int id;
    std::string source;
    std::string trans;
    int width;
    int height;

    TMX_image();

    void init(const tinyxml2::XMLElement *element);
};


#endif //SDLXX_TXM_IMAGE_H
