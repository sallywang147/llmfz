#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mz_zip.h"

// Define the callback function type
typedef int (*func_type)(void *handle, void *userdata, mz_zip_reader_entry_cb entry_cb);

// Define a simple callback function
int simple_cb(void *handle, void *userdata, mz_zip_reader_entry_cb entry_cb) {
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Consume data for the handle and userdata parameters
    std::string handle_str = stream.ConsumeRandomLengthString();
    std::string userdata_str = stream.ConsumeRemainingBytesAsString();

    // Convert the consumed strings to char pointers
    char* handle = const_cast<char*>(handle_str.c_str());
    char* userdata = const_cast<char*>(userdata_str.c_str());

    // Call the function to fuzz
    mz_zip_locate_first_entry(handle, userdata, simple_cb);

    return 0;
}