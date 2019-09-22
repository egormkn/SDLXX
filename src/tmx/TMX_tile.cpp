#include <tmx/TMX_tile.h>

TMX_tile::TMX_tile() {
    id = -1;
    width = 0;
    height = 0;
}

void TMX_tile::init(const tinyxml2::XMLElement *element) {
    if (element == nullptr) {
        return;
    }
    id = TMX_Utils::getAttributeInt(element, "id");
    width = TMX_Utils::getAttributeInt(element, "width");
    height = TMX_Utils::getAttributeInt(element, "height");
    tmx_image.init(element->FirstChildElement("image"));
    tmx_objectgroup.init(element->FirstChildElement("objectgroup"));
}
