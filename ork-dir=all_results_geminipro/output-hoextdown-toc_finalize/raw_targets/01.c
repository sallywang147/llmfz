#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "document.h"
#include "html.h"
#include "toc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegral<size_t>();
  hoedown_buffer* buffer = hoedown_buffer_new(buffer_size);
  if (buffer == nullptr) {
    return 0;
  }
  const int inline_render = stream.ConsumeBool();
  hoedown_renderer_data* data =
      static_cast<hoedown_renderer_data*>(malloc(sizeof(hoedown_renderer_data)));
  if (data == nullptr) {
    hoedown_buffer_free(buffer);
    return 0;
  }
  toc_finalize(buffer, inline_render, data);
  hoedown_buffer_free(buffer);
  free(data);
  return 0;
}