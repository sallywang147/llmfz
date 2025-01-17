#include <cstddef>
#include <cstdint>
#include <terminal/completeterminal.h>
#include <terminal/parser.h>

extern "C" {
#include "src/statesync/completeterminal.h"
#include "src/terminal/parser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Complete complete(80, 24);
  Terminal::Complete existing(80, 24);
  for (size_t i = 0; i < size; i++) {
    complete.act(Parser::UserByte(data[i]));
  }

  // Define a simple callback function for diff_from
  void DiffCallback(Terminal::Complete::DiffType type, int x, int y, int w, int h) {
    // Do something with the difference information
  }

  // Call diff_from with the callback function
  complete.diff_from(existing, DiffCallback);

  return 0;
}