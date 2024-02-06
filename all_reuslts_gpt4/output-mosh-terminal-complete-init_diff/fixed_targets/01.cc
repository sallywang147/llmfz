#include <cstddef>
#include <cstdint>

#include "src/statesync/completeterminal.h"
#include "src/terminal/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Complete complete1(80, 24);
  Terminal::Complete complete2(80, 24);
  for (size_t i = 0; i < size; i++) {
    complete1.act(Parser::UserByte(data[i]));
    complete2.act(Parser::UserByte(data[i]));
  }
  complete1.init_diff(&complete2);

  return 0;
}