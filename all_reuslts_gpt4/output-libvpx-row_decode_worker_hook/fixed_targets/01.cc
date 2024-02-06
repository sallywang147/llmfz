#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string str1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string str2 = stream.ConsumeRemainingBytesAsString();

  row_decode_worker_hook(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()));

  return 0;
}