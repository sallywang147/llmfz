#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cache/cache_varnishd.h"
#include "vapi/vsb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a VSB (Varnish String Builder) object
  struct vsb vsb;
  AN(VSB_init(&vsb, NULL, 0));

  // Create a WS (Workspace) object
  struct ws ws;
  WS_Init(&ws, "workspace", NULL, 0);

  // Call the function to fuzz
  WS_Panic(&vsb, &ws);

  // Cleanup
  VSB_destroy(&vsb);

  return 0;
}