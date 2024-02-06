#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract name_len
  size_t name_len = stream.ConsumeIntegral<size_t>();
  
  // Extract name
  std::vector<size_t> name = stream.ConsumeBytes<size_t>(name_len);
  
  // Extract val
  int val = stream.ConsumeIntegral<int>();

  // Call the function
  int result = register_int_index(name.data(), name_len, val);

  return 0;
}