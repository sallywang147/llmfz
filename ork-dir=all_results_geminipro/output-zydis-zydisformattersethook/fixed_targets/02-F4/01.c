#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "Zydis/Zydis.h"

extern "C" {
#include "Zydis/Formatter.h"
}

// Declare the ZydisFormatterHook type and the ZydisFormatterSetHook function in the global scope.
typedef int (*ZydisFormatterHook)(ZydisFormatter* formatter, ZyanU64 offset, ZydisString* string);
ZydisStatus ZydisFormatterSetHook(ZydisFormatter* formatter, ZyanU64 offset, ZydisFormatterHook hook_function);

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