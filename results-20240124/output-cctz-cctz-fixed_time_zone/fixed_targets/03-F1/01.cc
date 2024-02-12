#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/civil_time.h"
#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	FuzzedDataProvider fuzzed_data(data, size);

	cctz::time_zone::Impl * tz = cctz::fixed_time_zone(
			std::chrono::hours(fuzzed_data.ConsumeIntegral<int>()));

	std::string format = fuzzed_data.ConsumeRandomLengthString();
	cctz::format(format, cctz::convert(cctz::civil_second(
			fuzzed_data.ConsumeIntegral<uint32_t>(),
			fuzzed_data.ConsumeIntegral<uint32_t>(),
			fuzzed_data.ConsumeIntegral<uint32_t>(),
			fuzzed_data.ConsumeIntegral<uint32_t>(),
			fuzzed_data.ConsumeIntegral<uint32_t>(),
			fuzzed_data.ConsumeIntegral<uint32_t>()), *tz));

	return 0;
}