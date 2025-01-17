#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Create a FuzzedDataProvider instance.
    FuzzedDataProvider stream(data, size);
    
    // Create a new XML parser
    XML_Parser parser = XML_ParserCreate(NULL);
    if (!parser) {
        return 0;
    }

    // Consume the data as a string
    std::string base = stream.ConsumeRemainingBytesAsString();
    
    // Call the function to be fuzzed
    XML_SetBase(parser, const_cast<char*>(base.c_str()));

    // Free the parser
    XML_ParserFree(parser);

    return 0;
}