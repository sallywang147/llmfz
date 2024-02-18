#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
	FuzzedDataProvider fuzzed_data(data, size);
	float float_value = fuzzed_data.ConsumeFloatingPoint<float>();
	double double_value = fuzzed_data.ConsumeFloatingPoint<double>();
	int int_value = fuzzed_data.ConsumeIntegral<int>();
	bool bool_value = fuzzed_data.ConsumeBool();
	std::string str1 = fuzzed_data.ConsumeRandomLengthString();
	std::string str2 = fuzzed_data.ConsumeRemainingBytesAsString();

	std::string float_str = absl::StrFormat("%g", float_value);
	std::string double_str = absl::StrFormat("%g", double_value);
	std::string int_str = absl::StrFormat("%d", int_value);
	std::string bool_str = absl::StrFormat("%d", bool_value);

	absl::str_format_internal::FormatArgImpl::Dispatch<long>(
		(char *)float_str.c_str(), float_str.size(), 0, nullptr);
	absl::str_format_internal::FormatArgImpl::Dispatch<long>(
		(char *)double_str.c_str(), double_str.size(), 0, nullptr);
	absl::str_format_internal::FormatArgImpl::Dispatch<long>(
		(char *)int_str.c_str(), int_str.size(), 0, nullptr);
	absl::str_format_internal::FormatArgImpl::Dispatch<long>(
		(char *)bool_str.c_str(), bool_str.size(), 0, nullptr);

	absl::StrAppend(&str1, str2);
	std::string str_result = absl::StrCat(str1, float_value, double_value, int_value, bool_value);
	std::vector<std::string> v = absl::StrSplit(str_result, ".");
	absl::StrJoin(v, ".");
	return 0;
}