#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Zydis formatter.
  ZydisFormatter formatter;
  if (ZYAN_FAILED(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL))) {
    return 0;
  }

  // Initialize Zydis formatter buffer.
  ZydisFormatterBuffer buffer;
  if (ZYAN_FAILED(ZydisFormatterBufferInit(&buffer, 1024))) {
    return 0;
  }

  // Get a string from the formatter buffer.
  ZyanString* str;
  if (ZYAN_FAILED(ZydisFormatterBufferGetString(&buffer, &str))) {
    return 0;
  }

  return 0;
}