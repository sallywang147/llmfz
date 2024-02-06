#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  cctz::time_zone tz;
  std::string version;
  
  if (cctz::load_time_zone(stream.ConsumeRandomLengthString(), &tz)) {
    tz.version(&version, &tz);
  }
  
  return 0;
}