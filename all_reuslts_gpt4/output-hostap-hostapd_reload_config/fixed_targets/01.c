#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "hostapd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct hostapd_iface iface;
  iface.num_bss = provider.ConsumeIntegralInRange<int>(1, 8);

  for (int i = 0; i < iface.num_bss; i++) {
    iface.bss[i] = static_cast<struct hostapd_data*>(malloc(sizeof(struct hostapd_data)));
    if (iface.bss[i] == nullptr) {
      for (int j = 0; j < i; j++) {
        free(iface.bss[j]);
      }
      return 0;
    }
  }

  int result = hostapd_reload_config(&iface);

  for (int i = 0; i < iface.num_bss; i++) {
    free(iface.bss[i]);
  }

  return 0;
}