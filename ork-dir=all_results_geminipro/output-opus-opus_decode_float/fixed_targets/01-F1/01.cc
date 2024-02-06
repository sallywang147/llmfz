#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "opus/opus.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int sample_rate = stream.ConsumeIntegralInRange(8000, 48000);
  const int channels = stream.ConsumeIntegralInRange(1, 2);
  const int frame_size = stream.ConsumeIntegralInRange(20, 120);
  const int decode_fec = stream.ConsumeBool();

  OpusDecoder* decoder = opus_decoder_create(sample_rate, channels, &stream.ConsumeIntegral<int>());
  if (decoder == nullptr) {
    return 0;
  }

  const size_t pcm_size = frame_size * channels * sizeof(float);
  float* pcm = static_cast<float*>(std::malloc(pcm_size));
  if (pcm == nullptr) {
    opus_decoder_destroy(decoder);
    return 0;
  }

  const std::string input = stream.ConsumeRemainingBytesAsString();
  opus_decode_float(decoder, input.data(), input.size(), pcm, frame_size, decode_fec);

  std::free(pcm);
  opus_decoder_destroy(decoder);
  return 0;
}
```

The issue is that the `opus.h` header file is not wrapped with `extern "C" {}`. This is necessary because the header file contains C functions and data structures, which need to be declared with `extern "C"` in order to be visible to the C++ compiler.

To fix the issue, the `#include "opus/opus.h"` line should be wrapped with `extern "C" {}`. The corrected code is shown above.