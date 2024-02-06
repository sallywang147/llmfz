#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "document.h"
#include "html.h"
#include "toc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();

  hoedown_buffer* ob = hoedown_buffer_new(64);
  hoedown_renderer_data* data = hoedown_malloc(sizeof(hoedown_renderer_data));
  data->toc_data = hoedown_toc_renderer_new(64);

  toc_finalize(ob, 0, data);

  hoedown_buffer_free(ob);
  hoedown_free(data->toc_data);
  hoedown_free(data);
  return 0;
}