#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    std::chrono::seconds offset(fuzzed_data.ConsumeIntegral<long long>());
    cctz::time_zone tz = cctz::fixed_time_zone(offset);
    cctz::time_zone lax = cctz::make_time_zone(tz.name());

    const auto t1 = cctz::convert(cctz::civil_second(
            fuzzed_data.ConsumeIntegral<uint32_t>(),
            fuzzed_data.ConsumeIntegral<uint32_t>(),
            fuzzed_data.ConsumeIntegral<uint32_t>(),
            fuzzed_data.ConsumeIntegral<uint32_t>(),
            fuzzed_data.ConsumeIntegral<uint32_t>(),
            fuzzed_data.ConsumeIntegral<uint32_t>()), lax);
    std::string format = fuzzed_data.ConsumeRandomLengthString();
    cctz::format(format, t1, lax);

    return 0;
}