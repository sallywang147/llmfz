#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/rdata.h"

struct AvahiRecord {
  int clazz;
  int type;
  union {
    uint32_t a;
    char* name;
  } data;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  AvahiRecord record;
  record.clazz = stream.ConsumeIntegral<int>();
  record.type = stream.ConsumeIntegral<int>();
  std::string name = stream.ConsumeRandomLengthString();
  record.data.name = const_cast<char*>(name.c_str());

  size_t max_size = stream.remaining_bytes();
  std::vector<char> rdata(max_size);
  
  avahi_rdata_serialize(&record, rdata.data(), max_size);

  return 0;
}