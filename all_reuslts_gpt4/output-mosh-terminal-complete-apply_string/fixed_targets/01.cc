#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "src/statesync/completeterminal.h"
#include "src/terminal/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string diff = stream.ConsumeRemainingBytesAsString();
  
  Terminal::Complete complete(80, 24);
  complete.apply_string(diff);
  
  return 0;
}