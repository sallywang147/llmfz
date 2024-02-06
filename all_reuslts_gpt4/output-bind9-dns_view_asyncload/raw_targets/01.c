#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "dns_view.h"

// Define a callback function of type func_type
void callback_func(char *arg) {
    // Do nothing. This function is just a placeholder for the callback.
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize dns_view
    struct dns_view *view = dns_view_new();

    // Extract boolean value
    bool newonly = stream.ConsumeBool();

    // Extract a string. Use .c_str() to use result as pointer
    std::string arg = stream.ConsumeRandomLengthString();
    char *arg_ptr = const_cast<char*>(arg.c_str());

    // Call the function to fuzz
    dns_view_asyncload(view, newonly, callback_func, arg_ptr);

    // Clean up
    dns_view_delete(view);

    return 0;
}