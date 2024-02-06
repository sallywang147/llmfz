#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int row_decode_worker_hook(char * , char * );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Divide the input data into two parts to use as the two char* parameters for the function.
  const size_t half_size = size / 2;
  std::string str1 = stream.ConsumeBytesAsString(half_size);
  std::string str2 = stream.ConsumeRemainingBytesAsString();

  // Pass the data to the function. As the function expects char* arguments, we need to get pointers to the string data.
  row_decode_worker_hook(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()));

  return 0;
}