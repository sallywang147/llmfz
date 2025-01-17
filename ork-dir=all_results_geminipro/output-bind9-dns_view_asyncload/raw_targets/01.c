#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "dns.h"
#include "dns_view.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  char* arg = provider.ConsumeBytesAsString().c_str();
  dns_view* view = dns_view_create();
  dns_view_asyncload(view, provider.ConsumeBool(), nullptr, arg);
  dns_view_delete(view);
  return 0;
}