#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cache/cache_varnishd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a struct vsb
  struct vsb vsb;
  AN(VSB_init(&vsb, NULL, 0));

  // Create a struct ws
  struct ws ws;
  WS_Init(&ws, "ws", NULL, 0);

  // Call the function under test
  ws_emu_panic(&vsb, &ws);

  // Clean up
  VSB_fini(&vsb);
  WS_Fini(&ws);

  return 0;
}