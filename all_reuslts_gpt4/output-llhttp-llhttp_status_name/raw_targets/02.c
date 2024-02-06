#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "llhttp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int status_code = stream.ConsumeIntegral<int>();
  char *status_name = llhttp_status_name(status_code);

  return 0;
}