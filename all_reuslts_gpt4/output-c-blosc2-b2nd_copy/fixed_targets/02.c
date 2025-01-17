#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

extern "C" {
    #include "b2nd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct b2nd_context_s context;
    struct b2nd_array_t array;
    struct b2nd_array_t.161 *array_ptr;

    // Initialize the context and array with data from the fuzzer
    if (stream.remaining_bytes() < sizeof(context) + sizeof(array)) {
        return 0;
    }
    stream.ConsumeData(&context, sizeof(context));
    stream.ConsumeData(&array, sizeof(array));

    // Call the function to be fuzzed
    b2nd_copy(&context, &array, &array_ptr);

    return 0;
}