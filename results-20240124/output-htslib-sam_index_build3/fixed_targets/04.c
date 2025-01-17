#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../htslib/hfile.h"
#include "../../htslib/hts.h"
#include "../../htslib/sam.h"

#include "Fuzzer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    const char *fn = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size)).c_str();
    const char *fnidx = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size)).c_str();
    const int min_shift = stream.ConsumeIntegralInRange<int>(-100, 100);
    const int nthreads = stream.ConsumeIntegralInRange<int>(0, 100);

    int ret = sam_index_build3((char *)fn, (char *)fnidx, min_shift, nthreads);

    return 0;
}