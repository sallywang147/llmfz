#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

extern "C" {
#include "cctz/civil_time.h"
#include "cctz/time_zone.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	FuzzedDataProvider fuzzed_data(data, size);

	std::chrono::duration<long long, std::ratio<1l, 1000000l> > offset;
	offset = std::chrono::seconds(fuzzed_data.ConsumeIntegral<int32_t>());

	cctz::time_zone::Impl *tz = cctz::fixed_time_zone(offset);

	return 0;
}