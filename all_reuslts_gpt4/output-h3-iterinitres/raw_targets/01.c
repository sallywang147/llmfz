#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
    #include "iterInitRes.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct IterCellsResolution res;
    int int_arg = stream.ConsumeIntegral<int>();

    iterInitRes(&res, int_arg);

    return 0;
}