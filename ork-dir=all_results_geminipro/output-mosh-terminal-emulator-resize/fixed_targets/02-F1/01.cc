#include <cstddef>
#include <cstdint>

extern "C" {
#include "src/terminal/emulator.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Emulator emulator;
  FuzzedDataProvider provider(data, size);
  size_t s_width = provider.ConsumeIntegral<size_t>();
  size_t s_height = provider.ConsumeIntegral<size_t>();
  emulator.resize(s_width, s_height);
  return 0;
}