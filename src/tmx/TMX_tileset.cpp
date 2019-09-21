#include "TMX_tileset.h"

TMX_tileset::TMX_tileset() {
    firstgid = TMX_Utils::DEFAULT_INT;
    source = TMX_Utils::DEFAULT_STRING;
    name = TMX_Utils::DEFAULT_STRING;
    tilewidth = TMX_Utils::DEFAULT_INT;
    tileheight = TMX_Utils::DEFAULT_INT;
    spacing = TMX_Utils::DEFAULT_INT;
    margin = TMX_Utils::DEFAULT_INT;
    tilecount = TMX_Utils::DEFAULT_INT;
    columns = TMX_Utils::DEFAULT_INT;
}

void TMX_tileset::init(const tinyxml2::XMLElement *element) {
    if (element == nullptr) {
        return;
    }
    firstgid = TMX_Utils::getAttributeInt(element, "firstgid");
    source = TMX_Utils::getAttributeString(element, "source");
    name = TMX_Utils::getAttributeString(element, "name");
    tilewidth = TMX_Utils::getAttributeInt(element, "tilewidth");
    tileheight = TMX_Utils::getAttributeInt(element, "tileheight");
    spacing = TMX_Utils::getAttributeInt(element, "spacing");
    margin = TMX_Utils::getAttributeInt(element, "margin");
    tilecount = TMX_Utils::getAttributeInt(element, "tilecount");
    columns = TMX_Utils::getAttributeInt(element, "columns");

    tmx_image.init(element->FirstChildElement("image"));
    for (const tinyxml2::XMLElement *e = element->FirstChildElement("tile"); e != NULL; e = e->NextSiblingElement("tile")) {
        TMX_tile tile;
        tile.init(e);
        tmx_tiles.push_back(tile);
    }
}

#include "TMX_tileset.h"
