#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/rdata.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the record structure
  struct AvahiRecord record;
  record.ref = stream.ConsumeIntegral<uint32_t>();
  record.flags = stream.ConsumeIntegral<uint32_t>();
  record.ttl = stream.ConsumeIntegral<uint32_t>();
  record.key = nullptr; // We don't have a way to generate a valid AvahiKey*
  record.data = nullptr; // We don't have a way to generate a valid AvahiRData*

  // Prepare the rdata buffer
  size_t max_size = stream.remaining_bytes();
  char* rdata = (char*) malloc(max_size);
  if (!rdata) {
    return 0;
  }

  // Call the function under test
  avahi_rdata_serialize(&record, rdata, max_size);

  free(rdata);
  return 0;
}