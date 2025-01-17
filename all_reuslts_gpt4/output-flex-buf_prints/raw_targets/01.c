#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "buf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct Buf *buf = buf_new();

    // Consume two strings from the input data
    std::string fmt = stream.ConsumeRandomLengthString();
    std::string s = stream.ConsumeRemainingBytesAsString();

    buf_prints(buf, const_cast<char*>(fmt.c_str()), const_cast<char*>(s.c_str()));

    buf_free(buf);

    return 0;
}