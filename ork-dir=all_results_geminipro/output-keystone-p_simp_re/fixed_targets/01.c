#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pcre2.h"

extern "C" {
#include "pcre2_ext.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    pcre2_config(PCRE2_CONFIG_JIT, false);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  const size_t pattern_size = provider.ConsumeIntegralInRange<size_t>(
      0, std::min(size, static_cast<size_t>(1 << 10)));
  const auto pattern = provider.ConsumeBytes<char>(pattern_size);
  const size_t subject_size = provider.ConsumeIntegralInRange<size_t>(
      0, std::min(size - pattern_size, static_cast<size_t>(1 << 10)));
  const auto subject = provider.ConsumeBytes<char>(subject_size);

  pcre2_code* re = pcre2_compile(
      reinterpret_cast<const uint8_t*>(pattern.data()),
      pattern_size,
      0,
      &provider.ConsumeIntegral<int>(),
      nullptr,
      nullptr);
  if (re == nullptr) {
    return 0;
  }

  pcre2_match_data* match_data = pcre2_match_data_create_from_pattern(re, nullptr);
  if (match_data == nullptr) {
    pcre2_code_free(re);
    return 0;
  }

  const int result = pcre2_match(
      re,
      reinterpret_cast<const uint8_t*>(subject.data()),
      subject_size,
      0,
      0,
      match_data,
      nullptr);

  pcre2_match_data_free(match_data);
  pcre2_code_free(re);

  // Call the function `p_simp_re` here.
  p_simp_re(nullptr, result);

  return 0;
}

// Define the function `p_simp_re` here.
extern "C" int p_simp_re(struct parse* /*parse*/, int result) {
  return result;
}