#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "brotli/encode.h"

extern "C" {
#include "brotli/c/include/brotli/encode.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int quality = stream.ConsumeIntegral<int>();
  const int lgwin = stream.ConsumeIntegral<int>();
  const int block_type = stream.ConsumeIntegral<int>();
  const size_t input_size = stream.ConsumeIntegral<size_t>();
  std::string input_str = stream.ConsumeBytesAsString(input_size);
  size_t output_size = stream.ConsumeIntegral<size_t>();
  std::string output_str = stream.ConsumeBytesAsString(output_size);

  BrotliEncoderCompress(quality, lgwin, (BrotliEncoderMode)block_type, input_size,
                        input_str.c_str(), &output_size, output_str.c_str());
  return 0;
}