 #include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/civil_time.h"
#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  cctz::time_zone lax;
  std::string tz = fuzzed_data.ConsumeRandomLengthString();
  if (load_time_zone(tz, &lax)) {
    std::chrono::system_clock::time_point tp;
    cctz::time_zone::civil_transition trans;
    bool result = lax.prev_transition(&tp, &trans);
    if (result) {
      std::cout << "Previous transition: " << trans.abbr << " "
                << trans.offset << "\n";
    }
  }

  return 0;
}