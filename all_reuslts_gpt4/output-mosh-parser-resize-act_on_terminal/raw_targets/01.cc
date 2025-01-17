#include <cstddef>
#include <cstdint>

#include "src/terminal/parser.h"
#include "src/terminal/terminal.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Emulator emulator(80, 24);
  Parser::Resize resize;
  resize.act_on_terminal(&emulator);

  return 0;
}