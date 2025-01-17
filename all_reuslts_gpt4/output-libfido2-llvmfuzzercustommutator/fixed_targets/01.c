#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" size_t LLVMFuzzerCustomMutator(char * data, size_t size, size_t maxsize, int seed);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data to initialize parameters for LLVMFuzzerCustomMutator
  std::string str = stream.ConsumeRandomLengthString();
  char* data_ptr = const_cast<char*>(str.c_str());
  size_t size_param = str.size();
  size_t maxsize_param = stream.ConsumeIntegral<size_t>();
  int seed_param = stream.ConsumeIntegral<int>();

  // Ensure maxsize_param is not less than size_param
  if (maxsize_param < size_param) {
    maxsize_param = size_param;
  }

  // Call the target function
  LLVMFuzzerCustomMutator(data_ptr, size_param, maxsize_param, seed_param);

  return 0;
}