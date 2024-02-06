#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <capstone/capstone.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct cs_struct ud;
    int result = ALPHA_global_init(&ud);

    return 0;
}