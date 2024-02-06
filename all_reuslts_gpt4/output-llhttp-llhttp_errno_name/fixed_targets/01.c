#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "llhttp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int error_code = stream.ConsumeIntegral<int>();
  llhttp_errno_name(error_code);

  return 0;
}