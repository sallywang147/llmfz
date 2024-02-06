#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hoedown.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct hoedown_buffer *ob = hoedown_buffer_new(64);
  struct hoedown_buffer *content = hoedown_buffer_new(64);
  struct hoedown_buffer *attr = hoedown_buffer_new(64);
  int level = stream.ConsumeIntegralInRange<int>(1, 6);

  struct hoedown_renderer_data data;
  data.opaque = NULL;

  if (stream.remaining_bytes() > 0) {
    size_t content_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    std::string content_str = stream.ConsumeBytesAsString(content_size);
    hoedown_buffer_puts(content, content_str.c_str());

    if (stream.remaining_bytes() > 0) {
      size_t attr_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
      std::string attr_str = stream.ConsumeBytesAsString(attr_size);
      hoedown_buffer_puts(attr, attr_str.c_str());
    }
  }

  toc_header(ob, content, attr, level, &data);

  hoedown_buffer_free(ob);
  hoedown_buffer_free(content);
  hoedown_buffer_free(attr);

  return 0;
}