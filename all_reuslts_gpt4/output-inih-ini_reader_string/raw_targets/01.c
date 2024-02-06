#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" char * ini_reader_string(char * str, int num, char * stream);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Consume a string for the `str` parameter.
  std::string str = provider.ConsumeRandomLengthString();
  // Consume an integer for the `num` parameter.
  int num = provider.ConsumeIntegral<int>();
  // Consume the remaining bytes as a string for the `stream` parameter.
  std::string stream = provider.ConsumeRemainingBytesAsString();

  // Call the function under test.
  ini_reader_string(const_cast<char*>(str.c_str()), num, const_cast<char*>(stream.c_str()));

  return 0;
}