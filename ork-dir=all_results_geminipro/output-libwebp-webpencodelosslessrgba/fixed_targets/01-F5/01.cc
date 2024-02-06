#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" {
  #include <webp/encode.h>
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t width = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  const size_t height = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  const size_t bytes_per_sample = stream.ConsumeIntegralInRange<size_t>(1, 4);
  const size_t input_size = width * height * bytes_per_sample;
  std::vector<uint8_t> input_buffer(input_size);
  stream.ConsumeBytes<uint8_t>(input_buffer.data(), input_size);

  size_t output_size = 0;
  uint8_t* output_buffer = WebPEncodeLosslessRGBA(
      reinterpret_cast<uint8_t*>(input_buffer.data()), width, height, bytes_per_sample,
      &output_size);
  free(output_buffer);
  return output_size;
}
```

The fixed code initializes the `output_size` variable to 0 and uses the return value of `WebPEncodeLosslessRGBA` to set the output size.