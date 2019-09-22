#include <tmx/TMX_data.h>

TMX_data::TMX_data() {
    encoding = TMX::Encoding::UNKNOWN;
    compression = TMX::Compression::UNKNOWN;
}

void TMX_data::init(const tinyxml2::XMLElement *element, int height, int width) {
    if (element == nullptr) {
        return;
    }
    encoding = TMX_Utils::getEncoding(element);
    compression = TMX_Utils::getCompression(element);
    data = TMX_Utils::parseMatrix(width, height, element->GetText());
}
