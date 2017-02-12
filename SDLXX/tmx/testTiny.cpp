//
// Created by Vlad on 09.02.2017.
//
#include "../../tinyxml2/tinyxml2.h"
#include "TMX_map.h"
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
    std::vector<int> a;
    for (int i = 10; i >= 0; --i) {
        a.push_back(i);
    }
    if (map_element != NULL) {
        map.init(map_element);
        //map.show();
    } else {
        std::cout << "map == NULL\n";
    }

    return 0;
}