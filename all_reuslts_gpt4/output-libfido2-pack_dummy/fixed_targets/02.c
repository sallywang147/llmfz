#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" size_t pack_dummy(char * ptr, size_t len);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the remaining bytes as a string.
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* ptr = str.c_str();
  size_t len = str.size();

  // Call the function under test.
  pack_dummy(ptr, len);

  return 0;
}