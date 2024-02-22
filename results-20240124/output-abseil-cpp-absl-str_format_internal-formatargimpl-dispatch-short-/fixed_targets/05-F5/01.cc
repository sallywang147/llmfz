#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"

extern "C" {
#include "absl/strings/str_format_internal.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
	FuzzedDataProvider fuzzed_data(data, size);
	short short_value = fuzzed_data.ConsumeIntegral<short>();
	std::string str1 = fuzzed_data.ConsumeRandomLengthString();
	std::string str2 = fuzzed_data.ConsumeRemainingBytesAsString();

	std::string short_str = absl::StrFormat("%d", short_value);

	// Call the Dispatch function to format the short value
	bool result = absl::str_format_internal::FormatArgImpl::Dispatch<short>(const_cast<char*>(short_str.c_str()), 0, 0, nullptr);
	if (!result) {
		return 0;
	}

	absl::StrAppend(&str1, str2);
	std::string str_result = absl::StrCat(str1, short_value);
	std::vector<std::string> v = absl::StrSplit(str_result, ".");
	absl::StrJoin(v, ".");
	return 0;
}