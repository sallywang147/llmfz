#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/rdata.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct AvahiRecord record;
  record.ref = stream.ConsumeIntegral<uint16_t>();
  record.klass = stream.ConsumeIntegral<uint16_t>();
  record.type = stream.ConsumeIntegral<uint16_t>();
  record.ttl = stream.ConsumeIntegral<uint32_t>();
  record.data = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();

  size_t max_size = stream.ConsumeIntegral<size_t>();
  char* rdata = new char[max_size];

  avahi_rdata_serialize(&record, rdata, max_size);

  delete[] rdata;

  return 0;
}