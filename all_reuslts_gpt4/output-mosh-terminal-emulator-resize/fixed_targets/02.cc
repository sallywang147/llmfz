#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>

#include "terminal.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(size_t) * 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  size_t s_width = stream.ConsumeIntegral<size_t>();
  size_t s_height = stream.ConsumeIntegral<size_t>();

  Terminal::Emulator emulator;
  emulator.resize(s_width, s_height);

  return 0;
}