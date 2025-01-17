#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ZydisFormatterHook hook_function = stream.ConsumeBool()
                                          ? [](ZydisFormatter* formatter,
                                               ZyanU64 offset,
                                               ZydisString* string) {
                                            return 0;
                                          }
                                          : nullptr;
  ZydisFormatterSetHook(nullptr, 0, &hook_function);
  return 0;
}