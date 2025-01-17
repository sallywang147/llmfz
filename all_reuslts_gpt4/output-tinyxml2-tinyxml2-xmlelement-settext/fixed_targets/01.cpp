#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    std::string str = stream.ConsumeRandomLengthString();
    char *ptr = const_cast<char*>(str.c_str());

    XMLDocument doc;
    XMLElement* element = doc.NewElement("TestElement");
    element->SetText(ptr);

    return 0;
}