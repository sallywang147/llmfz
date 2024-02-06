#include <cstddef>
#include <cstdint>

#include "src/terminal/parser.h"
#include "src/terminal/emulator.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  Terminal::Emulator emulator(80, 24);
  Parser::Resize resize(data[0], data[1]);
  resize.act_on_terminal(&emulator);

  return 0;
}