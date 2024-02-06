#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libtsm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    tsm_vte_new(&vte);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    int keysym = provider.ConsumeIntegral<int>();
    int ascii = provider.ConsumeIntegral<int>();
    int mods = provider.ConsumeIntegral<int>();
    int unicode = provider.ConsumeIntegral<int>();

    tsm_vte_handle_keyboard(vte, keysym, ascii, mods, unicode);
  }

  return 0;
}