#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "hoedown.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  struct hoedown_buffer* text_buffer = hoedown_buffer_new(size);
  hoedown_buffer_put(text_buffer, reinterpret_cast<const uint8_t*>(text.c_str()),
                     text.size());
  struct hoedown_buffer* ob = hoedown_buffer_new(size);
  struct hoedown_renderer_data* data = hoedown_malloc(sizeof(struct hoedown_renderer_data));
  rndr_raw_block(ob, text_buffer, data);
  hoedown_buffer_free(text_buffer);
  hoedown_buffer_free(ob);
  hoedown_free(data);
  return 0;
}