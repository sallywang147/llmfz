#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "planner.h"
#include "scanner.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();
  struct planner_s slate_planner;
  planner_init(&slate_planner, slate_width, slate_height);
  struct scanner_s slate_scanner;
  scanner_init(&slate_scanner, slate_width, slate_height);

  import(&slate_planner, &slate_scanner); // Fix the function name

  planner_free(&slate_planner);
  scanner_free(&slate_scanner);
  return 0;
}