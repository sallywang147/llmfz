#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "avahi-common/strlst.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct AvahiStringList * list = nullptr;

  while (stream.remaining_bytes() > 0) {
    std::string key = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size));
    std::string value = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size));

    list = avahi_string_list_add_pair(list, const_cast<char*>(key.c_str()), const_cast<char*>(value.c_str()));
  }

  avahi_string_list_free(list);

  return 0;
}