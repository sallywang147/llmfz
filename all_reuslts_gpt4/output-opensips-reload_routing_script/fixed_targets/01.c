#include <stdint.h>
#include <stddef.h>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" {
    #include "route.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Call the function with the fuzzed data
    int result = reload_routing_script();

    return 0;
}