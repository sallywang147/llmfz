#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../htslib/hts.h"
#include "../../htslib/sam.h"

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    const std::string filename = stream.ConsumeRandomLengthString();
    const std::string index_filename = stream.ConsumeRandomLengthString();
    const int min_shift = stream.ConsumeIntegral<int>();
    const int nthreads = stream.ConsumeIntegral<int>();
    sam_index_build3(const_cast<char*>(filename.c_str()),
                     const_cast<char*>(index_filename.c_str()),
                     min_shift,
                     nthreads);
    return 0;
}