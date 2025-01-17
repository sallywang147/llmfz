#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hoedown.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the hoedown_buffer structures
  struct hoedown_buffer *ob = hoedown_buffer_new(64);
  struct hoedown_buffer *text = hoedown_buffer_new(64);
  
  // Initialize the hoedown_renderer_data structure
  struct hoedown_renderer_data *rndr_data = (struct hoedown_renderer_data *)malloc(sizeof(struct hoedown_renderer_data));
  
  // Consume data for the text buffer
  std::string text_data = stream.ConsumeRemainingBytesAsString();
  hoedown_buffer_puts(text, text_data.c_str());

  // Call the target function
  rndr_raw_block(ob, text, rndr_data);

  // Clean up
  hoedown_buffer_free(ob);
  hoedown_buffer_free(text);
  free(rndr_data);

  return 0;
}