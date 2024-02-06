#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/civil_time.h"
#include "cctz/time_zone.h"
#include "cctz/time_zone_registry.h"

extern "C" {
#include "cctz/time_zone_registry.h"
int load_time_zone(const std::string& name, cctz::time_zone* tz);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  std::string tz = fuzzed_data.ConsumeRandomLengthString();
  cctz::time_zone lax;
  if (load_time_zone(tz, &lax)) {
    std::chrono::system_clock::time_point tp;
    cctz::time_zone::civil_transition trans;
    lax.prev_transition(&tp, &trans);
  }

  return 0;
}