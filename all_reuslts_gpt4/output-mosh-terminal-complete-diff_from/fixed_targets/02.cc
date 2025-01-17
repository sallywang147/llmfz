#include <cstddef>
#include <cstdint>

#include "src/statesync/completeterminal.h"
#include "src/terminal/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Complete complete1(80, 24);
  Terminal::Complete complete2(80, 24);

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    complete1.act(Parser::UserByte(provider.ConsumeIntegral<uint8_t>()));
    complete2.act(Parser::UserByte(provider.ConsumeIntegral<uint8_t>()));
  }

  complete1.diff_from(&complete2);

  return 0;
}