#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <dns/dns.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct dns_view* view = dns_view_create();
  if (view == nullptr) {
    return 0;
  }
  const bool value = stream.ConsumeBool();
  int ret = dns_view_freezezones(view, value);
  if (ret != 0) {
    return 0;
  }
  dns_view_delete(view);
  return 0;
}