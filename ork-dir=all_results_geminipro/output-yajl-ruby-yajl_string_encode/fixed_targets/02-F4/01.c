#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

extern "C" {
#include "yajl/yajl_gen.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a buffer to store the encoded string.
  yajl_buf buf = {0, 0, NULL};

  // Generate a string to encode.
  size_t string_length = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::string string_to_encode = provider.ConsumeRandomLengthString(string_length);

  // Generate a boolean value to indicate whether to HTML-escape the string.
  bool html_safe = provider.ConsumeBool();

  // Encode the string.
  yajl_string_encode(&buf, (const char*)string_to_encode.c_str(), string_to_encode.length(), html_safe);

  // Free the buffer.
  yajl_buf_free(&buf);

  return 0;
}