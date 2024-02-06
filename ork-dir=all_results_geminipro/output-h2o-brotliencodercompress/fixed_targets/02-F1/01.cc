#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "brotli/encode.h"

extern "C" {
#include "brotli/decode.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int quality = stream.ConsumeIntegral<int>();
  const int lgwin = stream.ConsumeIntegral<int>();
  const int block_size = stream.ConsumeIntegral<int>();
  const size_t input_size = stream.ConsumeIntegral<size_t>();
  const std::string input = stream.ConsumeRemainingBytesAsString();

  size_t output_size = 0;
  char* output = nullptr;
  BrotliEncoderCompress(quality, lgwin, block_size, input_size,
                        reinterpret_cast<const uint8_t*>(input.c_str()), &output_size,
                        &output);
  free(output);
  return 0;
}