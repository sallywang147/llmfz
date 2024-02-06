#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "mz_zip.h"

// Define the callback function type
typedef int (*func_type)(void *handle, void *userdata);

// Define a sample callback function
int sample_callback(void *handle, void *userdata) {
    // Do nothing in this callback function
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Extract a string for handle
    std::string handle_str = stream.ConsumeRandomLengthString();
    char *handle = const_cast<char*>(handle_str.c_str());

    // Extract a string for userdata
    std::string userdata_str = stream.ConsumeRandomLengthString();
    char *userdata = const_cast<char*>(userdata_str.c_str());

    // Call the target function
    mz_zip_locate_first_entry(handle, userdata, sample_callback);

    return 0;
}