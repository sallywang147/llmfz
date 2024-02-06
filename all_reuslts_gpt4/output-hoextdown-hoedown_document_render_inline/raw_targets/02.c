#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hoedown.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  hoedown_renderer *renderer = hoedown_html_renderer_new(0, 0);
  hoedown_document *document = hoedown_document_new(renderer, 0, 16);
  hoedown_buffer *ob = hoedown_buffer_new(64);

  std::string str = stream.ConsumeRemainingBytesAsString();
  char* ptr = const_cast<char*>(str.c_str());

  hoedown_document_render_inline(document, ob, ptr, size);

  hoedown_buffer_free(ob);
  hoedown_document_free(document);
  hoedown_html_renderer_free(renderer);

  return 0;
}