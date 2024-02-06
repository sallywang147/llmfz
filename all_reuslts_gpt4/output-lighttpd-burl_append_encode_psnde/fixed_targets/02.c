#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize a buffer
    struct buffer b;
    buffer_init(&b);

    // Consume the data as a string
    std::string str = stream.ConsumeRemainingBytesAsString();
    
    // Call the function to fuzz
    burl_append_encode_psnde(&b, str.c_str(), str.size());

    // Free the buffer
    buffer_free(&b);

    return 0;
}