#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint32_t width = stream.ConsumeIntegral<uint32_t>();
  const uint32_t height = stream.ConsumeIntegral<uint32_t>();
  const uint8_t bits_per_sample = stream.ConsumeIntegral<uint8_t>();
  const std::string input = stream.ConsumeRemainingBytesAsString();
  char* output = nullptr;
  size_t output_size = 0;
  const size_t ret = WebPEncodeLosslessBGRA(
      const_cast<char*>(input.c_str()), width, height, bits_per_sample, &output,
      &output_size);
  free(output);
  return 0;
}