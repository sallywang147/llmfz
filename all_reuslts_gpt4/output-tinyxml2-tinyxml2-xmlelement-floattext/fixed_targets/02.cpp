#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    float defaultValue = stream.ConsumeFloatingPoint<float>();
    std::string xml_string = stream.ConsumeRemainingBytesAsString();

    tinyxml2::XMLDocument doc;
    doc.Parse(xml_string.c_str());

    tinyxml2::XMLElement* root = doc.RootElement();
    if (root != nullptr) {
        root->FloatText(defaultValue);
    }

    return 0;
}