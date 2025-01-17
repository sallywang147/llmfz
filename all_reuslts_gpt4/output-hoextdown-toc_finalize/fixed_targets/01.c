#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hoedown.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  hoedown_buffer *ob = hoedown_buffer_new(64);
  if (!ob) {
    return 0;
  }

  int inline_render = provider.ConsumeBool();

  hoedown_renderer_data *renderer_data = new hoedown_renderer_data;
  if (!renderer_data) {
    hoedown_buffer_free(ob);
    return 0;
  }

  toc_finalize(ob, inline_render, renderer_data);

  hoedown_buffer_free(ob);
  delete renderer_data;

  return 0;
}