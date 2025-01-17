#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "dns_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Assume that the structure dns_zone has 4 int fields for simplicity
  struct dns_zone zone;
  zone.field1 = stream.ConsumeIntegral<int>();
  zone.field2 = stream.ConsumeIntegral<int>();
  zone.field3 = stream.ConsumeIntegral<int>();
  zone.field4 = stream.ConsumeIntegral<int>();

  std::string uap = stream.ConsumeRemainingBytesAsString();
  
  freezezones(&zone, const_cast<char *>(uap.c_str()));

  return 0;
}