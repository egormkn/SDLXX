//
// Created by Vlad on 09.02.2017.
//
#include "tinyxml2.h"
#include <tmx/TMX_map.h>
#include <vector>

int main(int argc, char *args[]) {
    tinyxml2::XMLDocument document;
    tinyxml2::XMLError result;
    result = document.LoadFile("resources/level.tmx");
    if (result != tinyxml2::XML_SUCCESS) {
        std::cout << "cannot parse\n";
    }
    tinyxml2::XMLElement *map_element = document.FirstChildElement("map");
    TMX_map map;
    if (map_element != NULL) {
        map.init(map_element);
        //map.show();
    } else {
        std::cout << "map == NULL\n";
    }

    std::vector<std::vector<int>> temp = TMX_Utils::parseMatrix(map.tmx_layers[0].width, map.tmx_layers[0].height, map.tmx_layers[0].tmx_data.data);

    return 0;
}
