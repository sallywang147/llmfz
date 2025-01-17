#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/civil_time.h"
#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	FuzzedDataProvider fuzzed_data(data, size);

	cctz::time_zone tz = cctz::local_time_zone();
	std::string tz_name = tz.name();
	std::string tz_abbrev = tz.abbreviation();
	cctz::time_zone lax;
	std::string tz_name2 = fuzzed_data.ConsumeRandomLengthString();
	if (load_time_zone(tz_name2, &lax)) {
		std::chrono::system_clock::time_point tp;
		std::string date_format = fuzzed_data.ConsumeRandomLengthString();
		std::string parse_format = fuzzed_data.ConsumeRandomLengthString();
		cctz::parse(parse_format, date_format, lax, &tp);

		const auto t1 = cctz::convert(cctz::civil_second(
				fuzzed_data.ConsumeIntegral<uint32_t>(),
				fuzzed_data.ConsumeIntegral<uint32_t>(),
				fuzzed_data.ConsumeIntegral<uint32_t>(),
				fuzzed_data.ConsumeIntegral<uint32_t>(),
				fuzzed_data.ConsumeIntegral<uint32_t>(),
				fuzzed_data.ConsumeIntegral<uint32_t>()), lax);
		std::string format = fuzzed_data.ConsumeRandomLengthString();
		cctz::format(format, t1, lax);
	}

	return 0;
}