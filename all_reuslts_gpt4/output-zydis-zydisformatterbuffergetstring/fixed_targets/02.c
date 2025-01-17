#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(ZydisFormatterBuffer_)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  ZydisFormatterBuffer_ buffer;
  ZyanString_ *string = nullptr;

  size_t consumed = stream.ConsumeData(&buffer, sizeof(buffer));
  if (consumed != sizeof(buffer)) {
    return 0;
  }

  ZydisFormatterBufferGetString(&buffer, &string);

  return 0;
}