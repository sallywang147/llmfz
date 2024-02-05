#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/rdata.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the AvahiRecord struct
  AvahiRecord record;
  record.ref = stream.ConsumeIntegral<uint32_t>();
  record.ttl = stream.ConsumeIntegral<uint32_t>();
  record.class_ = stream.ConsumeIntegral<uint16_t>();
  record.type = stream.ConsumeIntegral<uint16_t>();
  record.data = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size)).data();
  record.size = stream.ConsumeIntegral<uint16_t>();

  // Define and initialize the rdata buffer and max_size
  size_t max_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> rdata(max_size);

  // Call the target function
  avahi_rdata_serialize(&record, rdata.data(), max_size);

  return 0;
}