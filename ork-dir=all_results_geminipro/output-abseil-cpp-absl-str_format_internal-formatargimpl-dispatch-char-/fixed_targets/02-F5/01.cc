#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "absl/strings/string_view.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string format_str = provider.ConsumeRandomLengthString();
  std::string arg_str = provider.ConsumeRandomLengthString();
  std::string spec_str = provider.ConsumeRandomLengthString();

  // Ensure that the format string contains a %s.
  if (format_str.find('%') == std::string::npos ||
      format_str.find('s') == std::string::npos) {
    return 0;
  }

  // Ensure that the spec string is a valid integer.
  int spec;
  if (!absl::SimpleAtoi(spec_str, &spec)) {
    return 0;
  }

  // Ensure that the output buffer is large enough to hold the formatted string.
  std::vector<char> output_buffer(format_str.size() + arg_str.size());

  // Call the function to be fuzzed.
  bool result = absl::str_format_internal::FormatArgImpl::Dispatch<char>(
      arg_str.data(), spec, output_buffer.size(), output_buffer.data());

  // Check the result of the function call.
  if (!result) {
    return 0;
  }

  // Check that the output string is valid UTF-8.
  if (!absl::IsValidUTF8(output_buffer.data())) {
    return 0;
  }

  // Split the output string into its components.
  std::vector<std::string> components = absl::StrSplit(
      std::string(output_buffer.data()), absl::ByString("%s"));

  // Check that the number of components is correct.
  if (components.size() != 2) {
    return 0;
  }

  // Check that the first component is equal to the format string.
  if (components[0] != format_str) {
    return 0;
  }

  // Check that the second component is equal to the argument string.
  if (components[1] != arg_str) {
    return 0;
  }

  return 0;
}