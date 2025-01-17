#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "cmark.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Consume data to create a string for markdown input
  std::string markdown = stream.ConsumeRemainingBytesAsString();
  
  // Consume data to create an integer for options
  int options = stream.ConsumeIntegral<int>();

  // Call the target function
  char *html = cmark_markdown_to_html(markdown.c_str(), markdown.size(), options);
  
  // The returned string is allocated and must be freed by the caller
  free(html);
  
  return 0;
}