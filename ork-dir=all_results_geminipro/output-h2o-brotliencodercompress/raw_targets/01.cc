#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "brotli/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int quality = stream.ConsumeIntegral<int>();
  const int lgwin = stream.ConsumeIntegral<int>();
  const int block_size = stream.ConsumeIntegral<int>();
  const size_t input_size = stream.ConsumeIntegral<size_t>();
  const std::string input = stream.ConsumeRemainingBytesAsString();

  size_t output_size = 0;
  std::string output;
  output.resize(input_size * 2);
  const int result = BrotliEncoderCompress(quality, lgwin, block_size, input_size,
                                          const_cast<char*>(input.data()),
                                          &output_size, output.data());
  if (result != BROTLI_RESULT_SUCCESS) {
    return 0;
  }
  output.resize(output_size);
  return 0;
}