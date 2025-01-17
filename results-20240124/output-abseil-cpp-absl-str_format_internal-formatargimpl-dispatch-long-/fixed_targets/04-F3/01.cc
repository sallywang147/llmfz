#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
	FuzzedDataProvider fuzzed_data(data, size);
	long long_value = fuzzed_data.ConsumeIntegral<long>();
	std::string long_str = absl::StrFormat("%ld", long_value);
	bool result = absl::str_format_internal::FormatArgImpl::Dispatch<long>(
	    reinterpret_cast<char*>(&long_value), long_str.size(), 0, nullptr);
	return 0;
}