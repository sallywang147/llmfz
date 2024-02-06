#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "document.h"
#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a hoedown_document
  hoedown_renderer *renderer = hoedown_html_renderer_new(0, 0);
  hoedown_document *doc = hoedown_document_new(renderer, 0, 16);

  // Create a hoedown_buffer
  hoedown_buffer *ob = hoedown_buffer_new(64);

  // Extract a string
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *ptr = const_cast<char*>(str.c_str());

  // Call the function under test
  hoedown_document_render_inline(doc, ob, ptr, str.size());

  // Cleanup
  hoedown_buffer_free(ob);
  hoedown_document_free(doc);
  hoedown_html_renderer_free(renderer);

  return 0;
}