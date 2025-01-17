#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hoedown.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Creating buffer objects
  struct hoedown_buffer *ob = hoedown_buffer_new(64);
  struct hoedown_buffer *content = hoedown_buffer_new(64);
  struct hoedown_buffer *attr = hoedown_buffer_new(64);

  // Creating renderer data object
  struct hoedown_renderer_data data_obj;
  data_obj.opaque = nullptr;

  // Consuming data from the stream
  int level = stream.ConsumeIntegralInRange<int>(0, 6);
  std::string content_str = stream.ConsumeRandomLengthString();
  std::string attr_str = stream.ConsumeRemainingBytesAsString();

  // Populating the buffers
  hoedown_buffer_puts(content, content_str.c_str());
  hoedown_buffer_puts(attr, attr_str.c_str());

  // Calling the function to fuzz
  toc_header(ob, content, attr, level, &data_obj);

  // Cleaning up
  hoedown_buffer_free(ob);
  hoedown_buffer_free(content);
  hoedown_buffer_free(attr);

  return 0;
}