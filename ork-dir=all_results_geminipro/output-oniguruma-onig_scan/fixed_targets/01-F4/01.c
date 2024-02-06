#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <vector>

#include "oniguruma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a regex pattern buffer.
  OnigUChar* pattern =
      reinterpret_cast<OnigUChar*>(stream.ConsumeBytes<uint8_t>(size).data());
  OnigUChar* pattern_end = pattern + stream.ConsumeIntegral<size_t>();
  OnigRegex reg;
  OnigOptionType options = ONIG_OPTION_DEFAULT;
  OnigEncoding enc = ONIG_ENCODING_UTF8;
  int r = onig_new(&reg, pattern, pattern_end, options, enc, ONIG_SYNTAX_DEFAULT,
                  nullptr, nullptr);
  if (r != ONIG_NORMAL) {
    return 0;
  }

  // Create a region to store the results of the search.
  OnigRegion* region = onig_region_new();

  // Create a string to search.
  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> input = stream.ConsumeBytes<uint8_t>(input_size);
  OnigUChar* input_str =
      reinterpret_cast<OnigUChar*>(stream.ConsumeBytes<uint8_t>(size).data());
  OnigUChar* input_end = input_str + input_size;

  // Perform the search.
  r = onig_search(&reg, input_str, input_end, region, options);
  if (r >= 0) {
    // Print the results of the search.
    for (int i = 0; i < region->num_regs; i++) {
      OnigUChar* beg = input_str + region->beg[i];
      OnigUChar* end = input_str + region->end[i];
      printf("Match %d: %.*s\n", i, end - beg, beg);
    }
  }

  // Clean up.
  onig_region_free(region);
  onig_free(&reg);

  return 0;
}

extern "C" {
  #include "oniguruma.h"
}