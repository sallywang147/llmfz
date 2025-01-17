#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hoedown.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t ob_size = stream.ConsumeIntegralInRange<size_t>(0, size/2);
  std::vector<uint8_t> ob_data = stream.ConsumeBytes<uint8_t>(ob_size);
  struct hoedown_buffer *ob = hoedown_buffer_new(ob_size);
  hoedown_buffer_put(ob, ob_data.data(), ob_size);

  size_t text_size = stream.ConsumeIntegralInRange<size_t>(0, size/2);
  std::vector<uint8_t> text_data = stream.ConsumeBytes<uint8_t>(text_size);
  struct hoedown_buffer *text = hoedown_buffer_new(text_size);
  hoedown_buffer_put(text, text_data.data(), text_size);

  struct hoedown_renderer_data data;
  data.opaque = nullptr;

  rndr_raw_block(ob, text, &data);

  hoedown_buffer_free(ob);
  hoedown_buffer_free(text);

  return 0;
}