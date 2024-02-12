 #include <cstdint>
#include <cstddef>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
	FuzzedDataProvider fuzzed_data(data, size);
	int64_t int_value = fuzzed_data.ConsumeIntegral<int64_t>();
	std::string int_str = absl::StrFormat("%d", int_value);
	
	absl::str_format_internal::FormatArgImpl::Dispatch<int64_t>(
		const_cast<char*>(int_str.c_str()), int_str.size(), 0, nullptr);
	return 0;
}