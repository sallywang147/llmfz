 #include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "planner.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct planner_s ego;
  struct scanner_s sc;
  planner_init(&ego);
  scanner_init(&sc);

  size_t consumed = 0;
  while (consumed < size) {
    if (provider.ConsumeBool()) {
      planner_set_goal(&ego, provider.ConsumeIntegral<double>(),
                       provider.ConsumeIntegral<double>());
    } else {
      scanner_scan(&sc, provider.ConsumeIntegral<double>(),
                   provider.ConsumeIntegral<double>());
    }
    consumed += provider.ConsumeIntegral<uint8_t>();
  }

  imprt(&ego, &sc);
  return 0;
}