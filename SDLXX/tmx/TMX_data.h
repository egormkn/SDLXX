#ifndef SDLXX_TMX_DATA_H
#define SDLXX_TMX_DATA_H

#include "../../tinyxml2/tinyxml2.h"
#include "TMX_Utils.h"
#include <string>

class TMX_data {
public:
    TMX::Encoding encoding;
    TMX::Compression compression;
    const char *data;

    TMX_data();

    void init(const tinyxml2::XMLElement *element);
};


#endif //SDLXX_TMX_DATA_H
