#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "pcre2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string pattern = stream.ConsumeRemainingBytesAsString();
  const std::string subject = stream.ConsumeRemainingBytesAsString();

  pcre2_code* code = pcre2_compile(
      reinterpret_cast<const uint8_t*>(pattern.c_str()), pattern.size(),
      PCRE2_ZERO_TERMINATED | PCRE2_UTF, &stream.ConsumeIntegral<int>(),
      nullptr, nullptr);
  if (code == nullptr) {
    return 0;
  }

  pcre2_match_data* match_data =
      pcre2_match_data_create_from_pattern(code, nullptr);
  if (match_data == nullptr) {
    pcre2_code_free(code);
    return 0;
  }

  int rc = pcre2_match(code, reinterpret_cast<const uint8_t*>(subject.c_str()),
                       subject.size(), 0, PCRE2_NOTEMPTY, match_data, nullptr);
  pcre2_match_data_free(match_data);
  pcre2_code_free(code);
  return 0;
}