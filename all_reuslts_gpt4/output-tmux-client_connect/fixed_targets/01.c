#include <fuzzer/FuzzedDataProvider.h>

#include "client.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    
    // Initialize the event_base
    struct event_base* base = event_base_new();

    // Generate path from the fuzzer data
    std::string path = stream.ConsumeRandomLengthString();
    char *path_ptr = const_cast<char*>(path.c_str());

    // Generate flags from the fuzzer data
    size_t flags = stream.ConsumeIntegral<size_t>();

    // Call the function to fuzz
    client_connect(base, path_ptr, flags);

    // Clean up
    event_base_free(base);

    return 0;
}