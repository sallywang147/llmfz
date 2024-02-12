 #include <config.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../htslib/hts.h"
#include "../../htslib/sam.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    const std::string filename = stream.ConsumeRemainingBytesAsString();
    char *fn = strdup(filename.c_str());
    char *fnidx = strdup(filename.c_str());
    strcat(fnidx, ".bai");
    const int min_shift = stream.ConsumeIntegralInRange<int>(0, 10);
    sam_index_build2(fn, fnidx, min_shift);
    free(fn);
    free(fnidx);
    return 0;
}