#include <tmx/TMX_image.h>

TMX_image::TMX_image() {
    format = TMX_Utils::DEFAULT_STRING;
    id = TMX_Utils::DEFAULT_INT;
    source = TMX_Utils::DEFAULT_STRING;
    trans = TMX_Utils::DEFAULT_STRING;
    width = TMX_Utils::DEFAULT_INT;
    height = TMX_Utils::DEFAULT_INT;
}

void TMX_image::init(const tinyxml2::XMLElement *element) {
    if (element == nullptr) {
        return;
    }
    format = TMX_Utils::getAttributeString(element, "format");
    id = TMX_Utils::getAttributeInt(element, "id");
    source = TMX_Utils::getAttributeString(element, "source");
    trans = TMX_Utils::getAttributeString(element, "trans");
    width = TMX_Utils::getAttributeInt(element, "width");
    height = TMX_Utils::getAttributeInt(element, "height");
}
