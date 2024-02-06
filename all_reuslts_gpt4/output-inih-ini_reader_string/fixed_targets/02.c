#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int num = stream.ConsumeIntegral<int>();
  std::string str = stream.ConsumeRandomLengthString();
  std::string ini_stream = stream.ConsumeRemainingBytesAsString();

  // Ensure that str and ini_stream are null-terminated.
  str.push_back('\0');
  ini_stream.push_back('\0');

  // Call the function under test.
  ini_reader_string(str.data(), num, ini_stream.data());

  return 0;
}