#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "zydis/zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  uint8_t* buffer = static_cast<uint8_t*>(malloc(buffer_size));
  stream.ConsumeBytes<uint8_t>(buffer, buffer_size);
  ZydisFormatterBuffer formatter_buffer;
  ZydisFormatterBufferInit(&formatter_buffer, buffer, buffer_size);

  ZyanString* string;
  int ret = ZydisFormatterBufferGetString(&formatter_buffer, &string);
  if (ret == ZYAN_STATUS_SUCCESS) {
    ZyanStringDestroy(string);
  }
  free(buffer);
  return 0;
}