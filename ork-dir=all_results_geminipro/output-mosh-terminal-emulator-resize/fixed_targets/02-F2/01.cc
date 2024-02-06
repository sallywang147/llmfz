#include <cstddef>
#include <cstdint>
#include <sstream>

extern "C" {
#include "src/terminal/emulator.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Emulator emulator;
  std::stringstream ss;
  ss << "width=" << size << "\n";
  emulator.write(ss.str());
  return 0;
}