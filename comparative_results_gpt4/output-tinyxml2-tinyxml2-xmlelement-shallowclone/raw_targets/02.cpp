#include "tinyxml2/tinyxml2.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    std::string xml_string = stream.ConsumeRemainingBytesAsString();
    
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError err = doc.Parse(xml_string.c_str());

    if (err == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement* rootElement = doc.RootElement();
        if (rootElement != nullptr) {
            tinyxml2::XMLNode* cloneNode = rootElement->ShallowClone(&doc);
            // Do something with cloneNode if needed
        }
    }

    return 0;
}