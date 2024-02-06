#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZydisFormatter formatter;
  if (ZYAN_SUCCESS(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL))) {
    int hookType = stream.ConsumeIntegral<int>();
    std::vector<char*> hookData;
    while (stream.remaining_bytes() > 0) {
      std::string str = stream.ConsumeRandomLengthString();
      hookData.push_back(const_cast<char*>(str.c_str()));
    }
    hookData.push_back(nullptr); // null-terminate the array

    ZydisFormatterSetHook(&formatter, hookType, hookData.data());
  }

  return 0;
}