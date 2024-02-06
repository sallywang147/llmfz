#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "cmark.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract integral values
  int options = stream.ConsumeIntegral<int>();

  // Extract a string
  std::string str = stream.ConsumeRemainingBytesAsString();
  FILE *file = fmemopen((void *)str.c_str(), str.size(), "r");
  if (file == nullptr) {
    return 0;
  }

  // Call the function
  cmark_node *node = cmark_parse_file(file, options);

  // Cleanup
  if (node != nullptr) {
    cmark_node_free(node);
  }
  fclose(file);

  return 0;
}