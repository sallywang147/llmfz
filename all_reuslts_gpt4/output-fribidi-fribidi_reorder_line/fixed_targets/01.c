#include <fuzzer/FuzzedDataProvider.h>
#include <fribidi.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize parameters for fribidi_reorder_line
  int flags = stream.ConsumeIntegral<int>();
  int len = stream.ConsumeIntegralInRange<int>(0, 100); // Limit length to 100 to prevent excessive memory consumption
  int False = stream.ConsumeIntegral<int>();
  int base_dir = stream.ConsumeIntegral<int>();
  std::vector<int> bidi_types(len, 0);
  std::vector<char> embedding_levels(len, 0);
  std::vector<int> visual_str(len, 0);
  std::vector<int> map(len, 0);

  // Call the function with the initialized parameters
  fribidi_reorder_line(flags, bidi_types.data(), len, False, base_dir, embedding_levels.data(), visual_str.data(), map.data());

  return 0;
}