#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "compressor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize compressor context
  struct CompressorContext *c = compressor_init();
  if (c == nullptr) {
    return 0;
  }

  // Extract finalize flag
  bool finalize = stream.ConsumeBool();

  // Extract input data for compressor
  size_t input_size = stream.remaining_bytes();
  char *input_data = reinterpret_cast<char *>(stream.ConsumeRemainingBytes().data());

  // Prepare output buffer
  size_t output_size = compressor_max_output_size(c, input_size);
  std::vector<char> output_data(output_size);

  // Initialize done variable
  size_t done = 0;

  // Call the target function
  int result = compressor_encode(c, finalize, input_data, input_size, &done);

  // Clean up
  compressor_free(c);

  return 0;
}