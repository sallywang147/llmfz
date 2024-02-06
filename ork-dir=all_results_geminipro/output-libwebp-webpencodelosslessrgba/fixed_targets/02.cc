#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include <webp/encode.h>
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t width = stream.ConsumeIntegral<size_t>();
  const size_t height = stream.ConsumeIntegral<size_t>();
  const size_t bits_per_sample = stream.ConsumeIntegral<size_t>();
  const std::vector<uint8_t> input_data = stream.ConsumeRemainingBytes<uint8_t>();

  size_t output_size = 0;
  char* output_data = nullptr;
  WebPEncodingError error = WebPEncodeLosslessRGBA(
      reinterpret_cast<const uint8_t*>(input_data.data()), width, height, bits_per_sample,
      &output_data, &output_size);
  if (error != WEBP_ENCODER_SUCCESS) {
    return 1;  // Return an error code if the encoding fails.
  }
  free(output_data);

  return 0;
}