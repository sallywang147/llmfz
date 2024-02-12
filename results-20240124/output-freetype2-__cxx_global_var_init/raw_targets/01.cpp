 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a vector of random size.
  std::vector<int> vec(stream.ConsumeIntegralInRange<size_t>(0, 100));

  // Fill the vector with random values.
  for (auto& elem : vec) {
    elem = stream.ConsumeIntegral<int>();
  }

  // Call the function to fuzz.
  __cxx_global_var_init();

  return 0;
}