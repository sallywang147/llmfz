#include <fuzzer/FuzzedDataProvider.h>
#include <ixml.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create a temporary file and write the data to it.
    char filename[] = "/tmp/fuzz-XXXXXX";
    int fd = mkstemp(filename);
    if (fd < 0) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Call the function to be fuzzed.
    struct _IXML_Document *doc = ixmlLoadDocument(filename);

    // Clean up.
    if (doc != NULL) {
        ixmlDocument_free(doc);
    }
    unlink(filename);

    return 0;
}