#include <cstddef>
#include <cstdint>

#include "src/statesync/completeterminal.h"
#include "src/terminal/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Complete complete(80, 24);
  Terminal::Complete existing(80, 24);
  for (size_t i = 0; i < size; i++) {
    complete.act(Parser::UserByte(data[i]));
  }
  complete.diff_from(existing, nullptr);

  return 0;
}