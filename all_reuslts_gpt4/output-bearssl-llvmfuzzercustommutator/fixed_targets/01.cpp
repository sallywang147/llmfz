#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data from the stream to use as parameters for the function
  size_t size_param = stream.ConsumeIntegral<size_t>();
  size_t max_size_param = stream.ConsumeIntegral<size_t>();
  int int_param = stream.ConsumeIntegral<int>();

  // Consume the remaining bytes in the stream as a string
  std::string str_param = stream.ConsumeRemainingBytesAsString();

  // Ensure the size of str_param is less than or equal to max_size_param
  if (str_param.size() > max_size_param) {
    str_param.resize(max_size_param);
  }

  // Call the function with the parameters
  size_t result = LLVMFuzzerCustomMutator(str_param.data(), size_param, max_size_param, int_param);

  return 0;
}