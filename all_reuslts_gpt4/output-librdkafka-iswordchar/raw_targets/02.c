#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  while (stream.remaining_bytes() > 0) {
    // Consume an integer from the stream
    int c = stream.ConsumeIntegral<int>();
    // Call the function to fuzz
    iswordchar(c);
  }

  return 0;
}