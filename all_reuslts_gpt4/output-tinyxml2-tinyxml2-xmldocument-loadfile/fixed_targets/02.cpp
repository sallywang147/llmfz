#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    std::string file_name = stream.ConsumeRandomLengthString();
    file_name += ".xml"; // Ensure it has a .xml extension

    // Write the data to a temporary file
    FILE* file = fopen(file_name.c_str(), "wb");
    if (!file) {
        return 0;
    }
    fwrite(data, sizeof(uint8_t), size, file);
    fclose(file);

    // Load the file using the function to be fuzzed
    XMLDocument doc;
    doc.LoadFile(file_name.c_str());

    // Clean up
    remove(file_name.c_str());

    return 0;
}