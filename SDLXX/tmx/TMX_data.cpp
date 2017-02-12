#include "TMX_data.h"

TMX_data::TMX_data() {
    encoding = TMX::Encoding::UNKNOWN;
    compression = TMX::Compression::UNKNOWN;
    data = NULL;
}

void TMX_data::init(const tinyxml2::XMLElement *element) {
    encoding = TMX_Utils::getEncoding(element);
    compression = TMX_Utils::getCompression(element);
    data = element->GetText();
}