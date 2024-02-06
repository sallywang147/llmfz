The build error is likely caused by the missing declaration of the function `ixheaacd_hbe_apply_ifft_224`. To fix this, the header file `ixheaacd_hbe_apply_ifft_224.h` needs to be included with the `extern "C"` directive.

The corrected code:
```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "ixheaacd_hbe_apply_ifft_224.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t float_count = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<float> input_buffer(float_count);
  std::vector<float> output_buffer(float_count);
  stream.ConsumeFloatingPointArray(input_buffer.data(), float_count);

  const int channel_count = stream.ConsumeIntegralInRange<int>(0, 10);
  const int window_size = stream.ConsumeIntegralInRange<int>(0, 10);

  ixheaacd_hbe_apply_ifft_224(input_buffer.data(), output_buffer.data(), channel_count, window_size);
  return 0;
}
```
With this change, the code should compile and run without errors.