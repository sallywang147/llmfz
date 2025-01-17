#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
	FuzzedDataProvider fuzzed_data(data, size);
	long long long_value = fuzzed_data.ConsumeIntegral<long long>();
	std::string str1 = fuzzed_data.ConsumeRandomLengthString();
	std::string str2 = fuzzed_data.ConsumeRemainingBytesAsString();

	std::string long_str = absl::StrFormat("%lld", long_value);

	// Call the function `bool absl::str_format_internal::FormatArgImpl::Dispatch<long long>(char * arg, size_t spec, int out, char * )` inside function `LLVMFuzzerTestOneInput`.
	if (!absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
		const_cast<char*>(long_str.c_str()), 0, 0, nullptr))
		return 0;

	absl::StrAppend(&str1, str2);
	std::string str_result = absl::StrCat(str1, long_value);
	std::vector<std::string> v = absl::StrSplit(str_result, ".");
	absl::StrJoin(v, ".");
	return 0;
}