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

  char* output_data = nullptr;
  size_t output_size = WebPEncodeLosslessRGBA(
      reinterpret_cast<const uint8_t*>(input_data.data()), width, height, bits_per_sample,
      &output_data);
  free(output_data);

  return 0;
}
```

The issue in the original code is that the input data is passed to `WebPEncodeLosslessRGBA` as a `char*`, but the function expects a `const uint8_t*`. This can lead to undefined behavior and crashes.

To fix this, the input data is casted to `const uint8_t*` before passing it to the function. This ensures that the data is passed in the correct format and that the function can process it correctly.