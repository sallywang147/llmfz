#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "avahi-common/defs.h"
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"
#include "avahi-common/string.h"
#include "avahi-core/string-list.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string key = stream.ConsumeRemainingBytesAsString();
  const std::string value = stream.ConsumeRemainingBytesAsString();

  struct AvahiStringList *l = avahi_string_list_add_pair(nullptr,
                                                        const_cast<char*>(key.c_str()),
                                                        const_cast<char*>(value.c_str()));
  avahi_string_list_free(l);

  return 0;
}