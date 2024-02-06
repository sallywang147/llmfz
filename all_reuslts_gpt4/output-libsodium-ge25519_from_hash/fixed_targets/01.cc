#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" void ge25519_from_hash(char *s, char *h);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need two strings for the function parameters.
  // We will split the input data into two equal halves and use them to initialize the strings.
  size_t half_size = size / 2;

  std::string s = stream.ConsumeBytesAsString(half_size);
  std::string h = stream.ConsumeRemainingBytesAsString();

  // Call the function under test.
  ge25519_from_hash(const_cast<char*>(s.c_str()), const_cast<char*>(h.c_str()));

  return 0;
}