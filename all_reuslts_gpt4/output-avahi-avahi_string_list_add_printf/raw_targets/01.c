#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/strlst.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  
  // Initialize an AvahiStringList
  struct AvahiStringList *l = nullptr;

  // Consume the data to create a format string
  std::string format = provider.ConsumeRemainingBytesAsString();

  // Call the target function
  l = avahi_string_list_add_printf(l, const_cast<char*>(format.c_str()));

  // Free the AvahiStringList
  avahi_string_list_free(l);

  return 0;
}