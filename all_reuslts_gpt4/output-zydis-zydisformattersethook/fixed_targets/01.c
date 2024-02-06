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
  if (ZYAN_FAILED(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL))) {
    return 0;
  }

  int hook = stream.ConsumeIntegral<int>();
  std::vector<char*> args;
  while (stream.remaining_bytes() > 0) {
    std::string arg = stream.ConsumeRandomLengthString();
    char* arg_cstr = strdup(arg.c_str());
    if (arg_cstr == nullptr) {
      for (char* ptr : args) {
        free(ptr);
      }
      return 0;
    }
    args.push_back(arg_cstr);
  }

  ZydisFormatterSetHook(&formatter, hook, args.data());

  for (char* ptr : args) {
    free(ptr);
  }

  return 0;
}