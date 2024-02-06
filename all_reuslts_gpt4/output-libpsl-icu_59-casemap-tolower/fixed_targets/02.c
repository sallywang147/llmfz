#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "unicode/casemap.h"
#include "unicode/edits.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    const std::string locale = stream.ConsumeRandomLengthString();
    const int options = stream.ConsumeIntegral<int>();
    const int srcLength = stream.remaining_bytes() / 2;
    std::vector<short> src = stream.ConsumeBytes<short>(srcLength);
    const int destCapacity = stream.ConsumeIntegral<int>();
    std::vector<short> dest(destCapacity);
    icu_59::Edits edits;
    int errorCode = 0;

    icu_59::CaseMap::toLower(locale.c_str(), options, src.data(), srcLength, dest.data(), destCapacity, &edits, &errorCode);

    return 0;
}