#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <webp/encode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Consume data for parameters
  int w = stream.ConsumeIntegralInRange<int>(1, 100);
  int h = stream.ConsumeIntegralInRange<int>(1, 100);
  int bps = stream.ConsumeIntegralInRange<int>(1, 4);
  float q = stream.ConsumeFloatingPointInRange<float>(0.0, 100.0);
  
  // Consume data for input buffer
  size_t in_size = w * h * bps;
  if (stream.remaining_bytes() < in_size) {
    return 0;
  }
  std::vector<char> in = stream.ConsumeBytes<char>(in_size);
  
  // Initialize output buffer
  char* out = nullptr;

  // Call the function to fuzz
  size_t result = WebPEncodeBGRA(in.data(), w, h, bps, q, &out);

  // Free the memory allocated by WebPEncodeBGRA
  if (out != nullptr) {
    free(out);
  }

  return 0;
}