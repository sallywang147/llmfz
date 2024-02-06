#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "hostapd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct hostapd_iface iface;
  iface.num_bss = stream.ConsumeIntegralInRange<int>(0, 10);

  for (int i = 0; i < iface.num_bss; i++) {
    iface.bss[i] = new struct hostapd_data;
    iface.bss[i]->radius = new struct radius_server_data;
    iface.bss[i]->radius->shared_secret = (unsigned char*)stream.ConsumeRandomLengthString().c_str();
    iface.bss[i]->radius->shared_secret_len = strlen((char*)iface.bss[i]->radius->shared_secret);
  }

  hostapd_reload_config(&iface);

  for (int i = 0; i < iface.num_bss; i++) {
    delete iface.bss[i]->radius;
    delete iface.bss[i];
  }

  return 0;
}