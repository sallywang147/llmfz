 #include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "brotli/encode.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  const std::vector<uint8_t> input_data = stream.ConsumeBytes<uint8_t>(input_size);

  const int quality = stream.ConsumeIntegralInRange<int>(0, 11);
  const int lgwin = stream.ConsumeIntegralInRange<int>(10, 24);
  const int lgblock = stream.ConsumeIntegralInRange<int>(0, 24);

  size_t output_size = input_size;
  std::vector<uint8_t> output_data(output_size);
  BrotliEncoderCompress(quality, lgwin, lgblock, input_size, input_data.data(),
                        &output_size, output_data.data());
  return 0;
}