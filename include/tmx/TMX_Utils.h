#ifndef SDLXX_TMX_UTILS_H
#define SDLXX_TMX_UTILS_H

#include "tinyxml2.h"
#include <string>
#include <vector>

namespace TMX {
    //enum classes for map attributes

    enum class Orientation {
        ORTHOGONAL, ISOMETRIC, STAGGERED, HEXAGONAL, UNKNOWN
    };

    enum class RenderOrder {
        RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP, UNKNOWN
    };

    enum class StaggerIndex {
        EVEN, ODD, UNKNOWN
    };

    enum class StaggerAxis {
        X, Y, UNKNOWN
    };

    //enum classes for data

    enum class Encoding {
        BASE64, CSV, UNKNOWN
    };

    enum class Compression {
        GZIP, ZLIB, UNKNOWN
    };
}

class TMX_Utils {
public:
    //constants

    static const std::string DEFAULT_STRING;
    static const int DEFAULT_INT;
    static const double DEFAULT_DOUBLE;


    //functions for map information

    static TMX::Orientation orientationFromString(const char *string);

    static TMX::RenderOrder renderOrderFromString(const char *string);

    static TMX::StaggerIndex staggerIndexFromString(const char *string);

    static TMX::StaggerAxis staggerAxisFromString(const char *string);

    static TMX::Orientation getOrientation(const tinyxml2::XMLElement *element);

    static TMX::RenderOrder getRenderOrder(const tinyxml2::XMLElement *element);

    static TMX::StaggerIndex getStaggerIndex(const tinyxml2::XMLElement *element);

    static TMX::StaggerAxis getStaggerAxis(const tinyxml2::XMLElement *element);

    //functions for data information

    static TMX::Encoding getEncodingFromString(const char *string);

    static TMX::Compression getCompressionFromCompression(const char *string);

    static TMX::Encoding getEncoding(const tinyxml2::XMLElement *element);

    static TMX::Compression getCompression(const tinyxml2::XMLElement *element);

    //functions for getting attributes

    static double getAttributeDouble(const tinyxml2::XMLElement *element, const char *name);

    static int getAttributeInt(const tinyxml2::XMLElement *element, const char *name);

    static std::string getAttributeString(const tinyxml2::XMLElement *element, const char *name);

    //parsing matrix string

    static std::vector<std::vector<int>> parseMatrix(unsigned int width, unsigned int height, const char *data);
};


#endif //SDLXX_TMX_UTILS_H
