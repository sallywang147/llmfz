#include <cstddef>
#include <cstdint>

extern "C" {
#include "src/statesync/completeterminal.h"
#include "src/terminal/parser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Complete complete(80, 24);
  std::string diff;
  for (size_t i = 0; i < size; i++) {
    complete.act(Parser::UserByte(data[i]));
  }
  complete.apply_string(&diff);

  return 0;
}