#include <fuzzer/FuzzedDataProvider.h>
#include <ixml.h>
#include <cstdio>
#include <filesystem>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    
    // Create a temporary file to store the input data
    char filename[] = "/tmp/fuzz-XXXXXX";
    int fd = mkstemp(filename);
    if (fd < 0) {
        return 0;
    }

    // Write the input data to the file
    std::string str = stream.ConsumeRemainingBytesAsString();
    write(fd, str.c_str(), str.size());
    close(fd);

    // Load the document
    struct _IXML_Document *doc = ixmlLoadDocument(filename);

    // Clean up
    if (doc != NULL) {
        ixmlDocument_free(doc);
    }
    std::filesystem::remove(filename);

    return 0;
}