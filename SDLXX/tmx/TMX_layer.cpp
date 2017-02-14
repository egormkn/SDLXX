#include "TMX_layer.h"

TMX_layer::TMX_layer() {
    name = TMX_Utils::DEFAULT_STRING;
    x = TMX_Utils::DEFAULT_INT;
    y = TMX_Utils::DEFAULT_INT;
    width = TMX_Utils::DEFAULT_INT;
    height = TMX_Utils::DEFAULT_INT;
    opacity = TMX_Utils::DEFAULT_DOUBLE;
    visible = TMX_Utils::DEFAULT_DOUBLE;
    offsetsx = TMX_Utils::DEFAULT_INT;
    offsety = TMX_Utils::DEFAULT_INT;
}

void TMX_layer::init(const tinyxml2::XMLElement *element) {
    name = TMX_Utils::getAttributeString(element, "name");
    x = TMX_Utils::getAttributeInt(element, "x");
    y = TMX_Utils::getAttributeInt(element, "y");
    width = TMX_Utils::getAttributeInt(element, "width");
    height = TMX_Utils::getAttributeInt(element, "height");
    opacity = TMX_Utils::getAttributeDouble(element, "opacity");
    visible = TMX_Utils::getAttributeDouble(element, "visible ");
    offsetsx = TMX_Utils::getAttributeInt(element, "offsetsx");
    offsety = TMX_Utils::getAttributeInt(element, "offsety");

    tmx_data.init(element->FirstChildElement("data"), height, width);
}