#ifndef SDLXX_TMX_DATA_H
#define SDLXX_TMX_DATA_H

#include "../../tinyxml2/tinyxml2.h"
#include "TMX_Utils.h"
#include <string>
#include <vector>

class TMX_data {
public:
    TMX::Encoding encoding;
    TMX::Compression compression;
    std::vector<std::vector<int>> data;

    TMX_data();

    void init(const tinyxml2::XMLElement *element, int height, int width);
};


#endif //SDLXX_TMX_DATA_H
