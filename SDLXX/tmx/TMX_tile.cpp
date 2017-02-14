#include "TMX_tile.h"

TMX_tile::TMX_tile() {
    id = -1;
}

void TMX_tile::init(const tinyxml2::XMLElement *element) {
    if (element == nullptr) {
        return;
    }
    id = TMX_Utils::getAttributeInt(element, "id");
    tmx_image.init(element->FirstChildElement("image"));
}
