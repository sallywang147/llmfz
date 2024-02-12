#include <stdint.h>
#include <stddef.h>

#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" {
#include "avahi-common/defs.h"
#include "avahi-common/error.h"
#include "avahi-common/string-list.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  AvahiStringList *l = avahi_string_list_new();
  if (l == nullptr) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  const std::string format = stream.ConsumeRemainingBytesAsString();
  avahi_string_list_add_printf(l, const_cast<char*>(format.c_str()));
  avahi_string_list_free(l);
  return 0;
}