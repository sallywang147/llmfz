#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "document.h"
#include "html.h"
#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extracting integral values
  int inline_render = stream.ConsumeBool();

  // Extracting an array of bytes as a vector
  size_t ob_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> ob_data = stream.ConsumeBytes<uint8_t>(ob_size);
  
  // Initialize hoedown_buffer
  struct hoedown_buffer *ob = hoedown_buffer_new(ob_size);
  hoedown_buffer_puts(ob, reinterpret_cast<const char*>(ob_data.data()));

  // Initialize hoedown_renderer_data
  struct hoedown_renderer_data *data = new hoedown_renderer_data;
  data->opaque = nullptr;

  // Call the target function
  toc_finalize(ob, inline_render, data);

  // Clean up
  hoedown_buffer_free(ob);
  delete data;

  return 0;
}