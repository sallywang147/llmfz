#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t width = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  const size_t height = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  const size_t bytes_per_sample = stream.ConsumeIntegralInRange<size_t>(1, 4);
  const size_t input_size = width * height * bytes_per_sample;
  std::vector<uint8_t> input_buffer(input_size);
  stream.ConsumeBytes<uint8_t>(input_buffer.data(), input_size);

  char* output_buffer = nullptr;
  const size_t output_size = WebPEncodeLosslessRGBA(
      reinterpret_cast<char*>(input_buffer.data()), width, height, bytes_per_sample,
      &output_buffer);
  free(output_buffer);
  return output_size;
}

extern "C" {
  #include <webp/encode.h>
}