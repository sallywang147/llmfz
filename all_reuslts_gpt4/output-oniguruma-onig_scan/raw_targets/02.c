#include <fuzzer/FuzzedDataProvider.h>
#include <oniguruma.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  OnigErrorInfo einfo;
  OnigRegion *region;
  OnigEncoding use_encs[1];

  use_encs[0] = ONIG_ENCODING_UTF8;
  onig_initialize(use_encs, sizeof(use_encs)/sizeof(use_encs[0]));

  unsigned char *pattern = fuzzed_data.ConsumeBytes<unsigned char>(fuzzed_data.ConsumeIntegralInRange<size_t>(0, size)).data();
  unsigned char *str     = fuzzed_data.ConsumeBytes<unsigned char>(fuzzed_data.ConsumeIntegralInRange<size_t>(0, size)).data();

  OnigRegex reg;
  int r = onig_new(&reg, pattern, pattern + strlen((char *)pattern),
                   ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8,
                   ONIG_SYNTAX_DEFAULT, &einfo);
  if (r != ONIG_NORMAL) {
    return 0;
  }

  region = onig_region_new();

  auto scan_callback = [](int num_matches, int match_at, struct OnigRegion *region, void *arg) {
    return 0;
  };

  onig_scan(reg, str, str + strlen((char *)str), region, ONIG_OPTION_DEFAULT, scan_callback, nullptr);

  onig_region_free(region, 1 /* 1:free self, 0:free contents only */);
  onig_free(reg);
  onig_end();

  return 0;
}