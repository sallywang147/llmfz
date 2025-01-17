#include <cstddef>
#include <cstdint>

extern "C" {
#include "src/parser/parser.h"
#include "src/terminal/terminal.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Emulator emulator;
  Parser::Resize resize;
  for (size_t i = 0; i < size; i++) {
    resize.act(Parser::UserByte(data[i]));
  }
  resize.act_on_terminal(&emulator);

  return 0;
}