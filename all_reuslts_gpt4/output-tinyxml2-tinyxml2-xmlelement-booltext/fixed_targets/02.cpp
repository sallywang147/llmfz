#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2/tinyxml2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    tinyxml2::XMLDocument doc;
    doc.Parse(reinterpret_cast<const char*>(data), size);
    tinyxml2::XMLElement* root = doc.RootElement();
    if (root) {
        bool defaultValue = stream.ConsumeBool();
        root->BoolText(defaultValue);
    }
    return 0;
}