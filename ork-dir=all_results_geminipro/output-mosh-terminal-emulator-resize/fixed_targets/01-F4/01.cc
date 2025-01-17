#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "src/fuzzer/fuzzed_data_provider.h"
#include "src/terminal/emulator.h"

extern "C" {
#include "src/fuzzer/fuzzed_data_provider.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  using namespace std;

  Terminal::Emulator emulator;
  FuzzedDataProvider stream(data, size);
  const size_t s_width = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  const size_t s_height = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  emulator.resize(s_width, s_height);

  return 0;
}