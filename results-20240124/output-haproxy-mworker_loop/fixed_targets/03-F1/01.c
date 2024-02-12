#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm> // Include the necessary header file.
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "mworker.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t* mworker_input = stream.ConsumeRemainingBytes();
  const size_t mworker_input_len = stream.remaining_bytes();

  mworker_init();
  mworker_loop(mworker_input, mworker_input_len);
  mworker_deinit();

  return 0;
}