//
// Created by Vlad on 08.02.2017.
//

#include "TMX_map.h"

TMX_map::TMX_map() {
    map = NULL;
    version = TMX_Utils::DEFAULT_DOUBLE;
    orientation = TMX::Orientation::UNKNOWN;
    renderOrder = TMX::RenderOrder::UNKNOWN;
    width = TMX_Utils::DEFAULT_INT;
    height = TMX_Utils::DEFAULT_INT;
    tileWidth = TMX_Utils::DEFAULT_INT;
    tileHeight = TMX_Utils::DEFAULT_INT;
    hexSideLength = TMX_Utils::DEFAULT_INT;
    staggerAxis = TMX::StaggerAxis::UNKNOWN;
    staggerIndex = TMX::StaggerIndex::UNKNOWN;
    backgroundColor = TMX_Utils::DEFAULT_STRING;
    nextObjectID = TMX_Utils::DEFAULT_INT;
}

bool TMX_map::init(const std::string fileDir) {
    tinyxml2::XMLDocument document;
    tinyxml2::XMLError result = document.LoadFile(fileDir.c_str());
    if (result != tinyxml2::XML_SUCCESS) {
        SDLXX::Log::error("[TMX_map] Can't open file");
        return false;
    }

    map =  document.FirstChildElement("map");
    version = TMX_Utils::getAttributeDouble(map, "version");
    orientation = TMX_Utils::getOrientation(map);
    renderOrder = TMX_Utils::getRenderOrder(map);
    width = TMX_Utils::getAttributeInt(map, "width");
    height = TMX_Utils::getAttributeInt(map, "height");
    tileWidth = TMX_Utils::getAttributeInt(map, "tilewidth");
    tileHeight = TMX_Utils::getAttributeInt(map, "tileheight");
    hexSideLength = TMX_Utils::getAttributeInt(map, "hexsidelength");
    staggerAxis = TMX_Utils::getStaggerAxis(map);
    staggerIndex = TMX_Utils::getStaggerIndex(map);
    backgroundColor = TMX_Utils::getAttributeString(map, "backgroundcolor");
    nextObjectID = TMX_Utils::getAttributeInt(map, "nextobjectid");

    tmx_tileset.init(map->FirstChildElement("tileset"));

    for (const tinyxml2::XMLElement *e = map->FirstChildElement("layer");
         e != NULL; e = e->NextSiblingElement("layer")) {
        TMX_layer tmxLayer;
        tmxLayer.init(e);
        tmx_layers.push_back(tmxLayer);

    }
}