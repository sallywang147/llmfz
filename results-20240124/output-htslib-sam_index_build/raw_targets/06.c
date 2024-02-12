 #include <config.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../htslib/sam.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    const std::string filename = stream.ConsumeRemainingBytesAsString();
    const char* fn = filename.c_str();
    const int min_shift = stream.ConsumeIntegral<int>();
    int ret = sam_index_build(const_cast<char*>(fn), min_shift);
    if (ret < 0) {
        abort();
    }
    return 0;
}