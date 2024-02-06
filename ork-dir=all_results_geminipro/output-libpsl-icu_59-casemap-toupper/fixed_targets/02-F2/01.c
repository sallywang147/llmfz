#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unicode/casemap.h"
#include "unicode/charsetdetector.h"

extern "C" {
#include "unicode/casemap.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    icu::Locale::setDefault(icu::Locale::getUS());
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  std::vector<uint16_t> input_buffer;
  std::vector<uint16_t> output_buffer(size);

  // Generate random input string.
  while (provider.remaining_bytes() > 0) {
    input_buffer.push_back(provider.ConsumeIntegral<uint16_t>());
  }

  // Convert input string to UTF-16.
  icu::UnicodeString input_string(
      reinterpret_cast<const char16_t*>(input_buffer.data()), input_buffer.size());

  // Convert input string to upper case.
  icu::CaseMap mapper;
  icu::UnicodeString output_string;
  mapper.toUpper(input_string, output_string);

  // Convert output string back to UTF-8.
  std::vector<char> output_buffer_utf8(output_string.length() + 1);
  output_string.extract(0, output_string.length(), output_buffer_utf8.data());

  // Check if the output string is valid UTF-8.
  if (!icu::CharsetDetector::isWellFormedUTF8(
          output_buffer_utf8.data(), output_buffer_utf8.size())) {
    return 0;
  }

  return 0;
}