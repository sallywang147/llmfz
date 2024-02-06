#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "pcre2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  pcre2_real_general_context_8* general_context = pcre2_general_context_create_8(NULL, NULL, NULL);
  if (general_context == NULL) {
    return 0;
  }

  std::vector<uint8_t> pattern = fuzzed_data.ConsumeBytes<uint8_t>(fuzzed_data.remaining_bytes() / 2);
  std::vector<uint8_t> options = fuzzed_data.ConsumeRemainingBytes<uint8_t>();

  int errorcode;
  PCRE2_SIZE erroroffset;
  pcre2_real_code_8* code = pcre2_compile_8(pattern.data(), pattern.size(), options.size(), &errorcode, &erroroffset, general_context);
  if (code == NULL) {
    pcre2_general_context_free_8(general_context);
    return 0;
  }

  pcre2_real_match_data_8* match_data = pcre2_match_data_create_from_pattern_8(code, general_context);
  if (match_data == NULL) {
    pcre2_code_free_8(code);
    pcre2_general_context_free_8(general_context);
    return 0;
  }

  pcre2_match_data_free_8(match_data);
  pcre2_code_free_8(code);
  pcre2_general_context_free_8(general_context);

  return 0;
}