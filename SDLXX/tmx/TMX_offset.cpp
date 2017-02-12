#include "TMX_offset.h"

TMX_offset::TMX_offset() {
    x = TMX_Utils::DEFAULT_INT;
    y = TMX_Utils::DEFAULT_INT;
}

void TMX_offset::init(const tinyxml2::XMLElement *element) {
    x = TMX_Utils::getAttributeInt(element, "x");
    y = TMX_Utils::getAttributeInt(element, "y");
}