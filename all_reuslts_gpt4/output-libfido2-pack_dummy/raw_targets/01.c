#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" size_t pack_dummy(char * ptr, size_t len);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume a string from the data provider
  std::string str = stream.ConsumeRemainingBytesAsString();
  
  // Call the function under test
  pack_dummy(str.data(), str.size());

  return 0;
}