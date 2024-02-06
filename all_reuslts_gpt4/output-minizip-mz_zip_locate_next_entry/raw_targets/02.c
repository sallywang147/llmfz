#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mz_zip.h"

// Define the callback function type
typedef int (*func_type)(void *handle, void *userdata);

// Define a simple callback function
int simple_callback(void *handle, void *userdata) {
    return 0; // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Consume a string for the handle
    std::string handle = stream.ConsumeRandomLengthString();
    // Consume a string for the userdata
    std::string userdata = stream.ConsumeRemainingBytesAsString();

    // Call the function with the fuzzed inputs
    mz_zip_locate_next_entry(const_cast<char*>(handle.c_str()), const_cast<char*>(userdata.c_str()), simple_callback);

    return 0;
}