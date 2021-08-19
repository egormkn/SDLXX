#include "TMX_Utils.h"

#include <iostream>
#include <vector>

//initialization of static constants

const std::string TMX_Utils::DEFAULT_STRING = "";
const int TMX_Utils::DEFAULT_INT = -1;
const double TMX_Utils::DEFAULT_DOUBLE = -1.0;


// functions for map information

TMX::Orientation TMX_Utils::orientationFromString(const char *string) {
    if (string == NULL) {
        return TMX::Orientation::UNKNOWN;
    }
    if (!strcmp(string, "orthogonal")) {
        return TMX::Orientation::ORTHOGONAL;
    }
    if (!strcmp(string, "isometric")) {
        return TMX::Orientation::ISOMETRIC;
    }
    if (!strcmp(string, "staggered")) {
        return TMX::Orientation::STAGGERED;
    }
    if (!strcmp(string, "hexagonal")) {
        return TMX::Orientation::HEXAGONAL;
    }
    return TMX::Orientation::UNKNOWN;
}

TMX::RenderOrder TMX_Utils::renderOrderFromString(const char *string) {
    if (string == NULL) {
        return TMX::RenderOrder::UNKNOWN;
    }
    if (!strcmp(string, "right-down")) {
        return TMX::RenderOrder::RIGHT_DOWN;
    }
    if (!strcmp(string, "right-up")) {
        return TMX::RenderOrder::RIGHT_UP;
    }
    if (!strcmp(string, "left-down")) {
        return TMX::RenderOrder::LEFT_DOWN;
    }
    if (!strcmp(string, "left-up")) {
        return TMX::RenderOrder::LEFT_UP;
    }
    return TMX::RenderOrder::UNKNOWN;
}

TMX::StaggerIndex TMX_Utils::staggerIndexFromString(const char *string) {
    if (string == NULL) {
        return TMX::StaggerIndex::UNKNOWN;
    }
    if (!strcmp(string, "even")) {
        return TMX::StaggerIndex::EVEN;
    }
    if (!strcmp(string, "odd")) {
        return TMX::StaggerIndex::ODD;
    }
    return TMX::StaggerIndex::UNKNOWN;
}

TMX::StaggerAxis TMX_Utils::staggerAxisFromString(const char *string) {
    if (string == NULL) {
        return TMX::StaggerAxis::UNKNOWN;
    }
    if (!strcmp(string, "x")) {
        return TMX::StaggerAxis::X;
    }
    if (!strcmp(string, "y")) {
        return TMX::StaggerAxis::Y;
    }
    return TMX::StaggerAxis::UNKNOWN;
}

TMX::Orientation TMX_Utils::getOrientation(const tinyxml2::XMLElement *element) {
    const char *temp = element->Attribute("orientation");
    return orientationFromString(temp);
}

TMX::RenderOrder TMX_Utils::getRenderOrder(const tinyxml2::XMLElement *element) {
    const char *temp = element->Attribute("renderorder");
    return renderOrderFromString(temp);
}

TMX::StaggerIndex TMX_Utils::getStaggerIndex(const tinyxml2::XMLElement *element) {
    const char *temp = element->Attribute("staggerindex");
    return staggerIndexFromString(temp);
}

TMX::StaggerAxis TMX_Utils::getStaggerAxis(const tinyxml2::XMLElement *element) {
    const char *temp = element->Attribute("staggerindex");
    return staggerAxisFromString(temp);
}

//functions for data information

TMX::Encoding TMX_Utils::getEncodingFromString(const char *string) {
    if (string == NULL) {
        return TMX::Encoding::UNKNOWN;
    }
    if (!strcmp(string, "base64")) {
        return TMX::Encoding::BASE64;
    }
    if (!strcmp(string, "csv")) {
        return TMX::Encoding::CSV;
    }
    return TMX::Encoding::UNKNOWN;
}

TMX::Compression TMX_Utils::getCompressionFromCompression(const char *string) {
    if (string == NULL) {
        return TMX::Compression::UNKNOWN;
    }
    if (!strcmp(string, "gzip")) {
        return TMX::Compression::GZIP;
    }
    if (!strcmp(string, "zlib")) {
        return TMX::Compression::ZLIB;
    }
    return TMX::Compression::UNKNOWN;
}

TMX::Encoding TMX_Utils::getEncoding(const tinyxml2::XMLElement *element) {
    const char *temp = element->Attribute("encoding");
    return getEncodingFromString(temp);
}

TMX::Compression TMX_Utils::getCompression(const tinyxml2::XMLElement *element) {
    const char *temp = element->Attribute("compression");
    return getCompressionFromCompression(temp);
}

//functions for getting attributes

double TMX_Utils::getAttributeDouble(const tinyxml2::XMLElement *element, const char *name) {
    double temp;
    tinyxml2::XMLError result = element->QueryDoubleAttribute(name, &temp);
    if (result != tinyxml2::XML_SUCCESS) {
        return -1;
    }
    return temp;
}

int TMX_Utils::getAttributeInt(const tinyxml2::XMLElement *element, const char *name) {
    int temp;
    tinyxml2::XMLError result = element->QueryIntAttribute(name, &temp);
    if (result != tinyxml2::XML_SUCCESS) {
        return -1;
    }
    return temp;
}

std::string TMX_Utils::getAttributeString(const tinyxml2::XMLElement *element, const char *name) {
    const char *temp = element->Attribute(name);
    if (temp != nullptr) {
        return std::string(temp);
    }
    return "";
}

//parsing matrix string

std::vector<std::vector<int>> TMX_Utils::parseMatrix(unsigned int width, unsigned int height, const char *data) {
    if (data == nullptr) {
        return std::vector<std::vector<int>>();
    }
    std::vector<std::vector<int>> matrix(height, std::vector<int>(width));
    std::string number;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            while (!isdigit((int) *data)) ++data;
            while (isdigit((int) *data)) {
                number.append(1, *data);
                ++data;
            }
            matrix[i][j] = atoi(number.c_str());
            number.clear();
        }
    }
    return matrix;
}
