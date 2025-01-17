#include <cstddef>
#include <cstdint>

#include "src/terminal/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Complete complete(80, 24);
  for (size_t i = 0; i < size; i++) {
    complete.act(Parser::UserByte(data[i]));
  }
  complete.init_diff(nullptr, nullptr);

  return 0;
}