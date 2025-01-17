#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  size_t max_size = stream.ConsumeIntegral<size_t>();
  int seed = stream.ConsumeIntegral<int>();
  
  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<char> buffer = stream.ConsumeRemainingBytes<char>();
  
  // Call the function with the fuzzed inputs
  LLVMFuzzerCustomMutator(buffer.data(), buffer.size(), max_size, seed);

  return 0;
}