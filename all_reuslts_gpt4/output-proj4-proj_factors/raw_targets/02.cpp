#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "proj.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    
    struct P5_FACTORS factors;
    struct PJconsts *pj;
    union PJ_COORD coord;
    
    // Initialize the PJconsts structure
    pj = static_cast<struct PJconsts *>(calloc(1, sizeof(struct PJconsts)));
    if (pj == NULL) {
        return 0;
    }

    // Initialize the PJ_COORD union
    coord.v[0] = stream.ConsumeFloatingPoint<double>();
    coord.v[1] = stream.ConsumeFloatingPoint<double>();
    coord.v[2] = stream.ConsumeFloatingPoint<double>();
    coord.v[3] = stream.ConsumeFloatingPoint<double>();

    // Call the function to fuzz
    proj_factors(&factors, pj, &coord);

    // Clean up
    free(pj);

    return 0;
}