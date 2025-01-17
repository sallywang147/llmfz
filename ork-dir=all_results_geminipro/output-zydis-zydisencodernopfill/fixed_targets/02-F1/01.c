#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "Zydis/Zydis.h"

extern "C" {
#include "Zydis/Zydis.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegral<size_t>();
  char* buffer = static_cast<char*>(malloc(buffer_size));
  if (buffer == nullptr) {
    return 0;
  }
  ZydisEncoderNopFill(buffer, buffer_size);
  free(buffer);
  return 0;
}