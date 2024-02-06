#include <fuzzer/FuzzedDataProvider.h>
#include <oniguruma.h>
#include <stdint.h>
#include <stdlib.h>

// Define a callback function for onig_scan
static int scan_callback(int number, int position, OnigRegion* region, void* arg) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }
  
  FuzzedDataProvider fuzzed_data(data, size);

  // Split data into two parts: one for the regex pattern, one for the string to scan
  const std::string regex_pattern = fuzzed_data.ConsumeBytesAsString(size / 2);
  const std::string str_to_scan = fuzzed_data.ConsumeRemainingBytesAsString();

  OnigErrorInfo einfo;
  OnigRegion *region;
  OnigRegex reg;

  // Compile the regex
  int r = onig_new(&reg, (const OnigUChar *)regex_pattern.c_str(), 
                   (const OnigUChar *)(regex_pattern.c_str() + regex_pattern.size()),
                   ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, &einfo);
  if (r != ONIG_NORMAL) {
    return 0;
  }

  region = onig_region_new();

  // Scan the string with the compiled regex
  onig_scan(reg, (const OnigUChar *)str_to_scan.c_str(),
            (const OnigUChar *)(str_to_scan.c_str() + str_to_scan.size()),
            region, ONIG_OPTION_DEFAULT, scan_callback, NULL);

  onig_region_free(region, 1 /* 1:free self, 0:free contents only */);
  onig_free(reg);
  onig_end();

  return 0;
}