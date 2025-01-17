#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "buffer.h"
#include "burl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct buffer b;
  buffer_init(&b);

  // Extract a string from the data provider.
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = str.c_str();

  // Call the function to fuzz.
  burl_append_encode_all(&b, ptr, str.size());

  buffer_free(&b);

  return 0;
}