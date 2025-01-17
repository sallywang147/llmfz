#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cache/cache.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a struct vsb
  struct vsb vsb;
  AN(vsb_new(&vsb, NULL, 0, VSB_AUTOEXTEND));

  // Initialize a struct ws
  struct ws ws[1];
  WS_Init(ws, "ws", NULL, 0);

  // Call the function to fuzz
  ws_emu_panic(&vsb, ws);

  // Cleanup
  vsb_delete(&vsb);

  return 0;
}