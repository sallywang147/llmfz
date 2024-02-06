#include <cstddef>
#include <cstdint>

#include "src/terminal/emulator.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Emulator emulator;
  FuzzedDataProvider stream(data, size);
  const size_t s_width = stream.ConsumeIntegral<size_t>();
  const size_t s_height = stream.ConsumeIntegral<size_t>();
  emulator.resize(s_width, s_height);

  return 0;
}