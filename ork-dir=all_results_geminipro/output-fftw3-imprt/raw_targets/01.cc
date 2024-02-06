#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "planner.h"
#include "scanner.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  planner_s planner;
  scanner_s scanner;

  // Initialize planner and scanner
  planner_init(&planner);
  scanner_init(&scanner);

  // Read fuzzed data into planner
  size_t bytes_read = 0;
  while (bytes_read < size) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(0, size - bytes_read);
    auto next_input = provider.ConsumeBytes<uint8_t>(next_size);
    planner_feed(&planner, next_input.data(), next_input.size());
    bytes_read += next_size;
  }

  // Call imprt function
  imprt(&planner, &scanner);

  // Cleanup
  planner_free(&planner);
  scanner_free(&scanner);

  return 0;
}