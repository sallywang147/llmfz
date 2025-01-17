#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0;
    }

    FuzzedDataProvider stream(data, size);

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLNode* parentNode = doc.NewElement("Parent");
    tinyxml2::XMLNode* childNode = doc.NewElement("Child");
    tinyxml2::XMLNode* newNode = doc.NewElement("NewNode");

    // Add childNode to parentNode
    parentNode->InsertEndChild(childNode);

    // Now try to insert newNode after childNode
    parentNode->InsertAfterChild(childNode, newNode);

    return 0;
}