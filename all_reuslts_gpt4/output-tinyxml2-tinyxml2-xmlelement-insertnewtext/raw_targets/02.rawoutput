#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create a new XMLDocument
    XMLDocument doc;

    // Create a new XMLElement
    XMLElement* elem = doc.NewElement("TestElement");

    // Extract a string from the data provider
    std::string text = stream.ConsumeRandomLengthString();

    // Insert the text into the element
    elem->InsertNewText(text.c_str());

    return 0;
}