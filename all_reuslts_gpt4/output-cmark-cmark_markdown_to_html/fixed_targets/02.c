#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "cmark.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int options = stream.ConsumeIntegral<int>();
  std::string markdown = stream.ConsumeRemainingBytesAsString();

  char* html = cmark_markdown_to_html(markdown.c_str(), markdown.size(), options);

  if (html) {
    free(html);
  }

  return 0;
}