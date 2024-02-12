#include <config.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../htslib/hts.h"
#include "../../htslib/sam.h"

#include <string>

#include "FuzzerDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    std::string filename = stream.ConsumeRandomLengthString();
    std::string filename_index = stream.ConsumeRandomLengthString();
    int min_shift = stream.ConsumeIntegral<int>();
    int nthreads = stream.ConsumeIntegral<int>();
    return sam_index_build3(const_cast<char*>(filename.c_str()),
                            const_cast<char*>(filename_index.c_str()), min_shift,
                            nthreads);
}