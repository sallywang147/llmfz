#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "pcre2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string pattern = stream.ConsumeRemainingBytesAsString();
  const size_t pattern_size = pattern.size();
  pcre2_code* re = pcre2_compile(reinterpret_cast<const uint8_t*>(pattern.c_str()),
                                pattern_size, 0, &stream.ConsumeIntegral<int>(),
                                nullptr, nullptr);
  if (re == nullptr) {
    return 0;
  }
  pcre2_match_data* match_data =
      pcre2_match_data_create_from_pattern(re, nullptr);
  if (match_data == nullptr) {
    pcre2_code_free(re);
    return 0;
  }
  pcre2_match_data_free(match_data);
  pcre2_code_free(re);
  return 0;
}