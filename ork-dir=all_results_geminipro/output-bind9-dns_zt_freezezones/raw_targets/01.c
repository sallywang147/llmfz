#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <dns/zt.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct dns_zt* zt = dns_zt_create();
  if (zt == nullptr) {
    return 0;
  }

  struct dns_view* view = dns_zt_view_create(zt);
  if (view == nullptr) {
    dns_zt_destroy(zt);
    return 0;
  }

  const bool freeze = stream.ConsumeBool();

  int ret = dns_zt_freezezones(zt, view, freeze);

  dns_zt_view_destroy(view);
  dns_zt_destroy(zt);

  return ret;
}