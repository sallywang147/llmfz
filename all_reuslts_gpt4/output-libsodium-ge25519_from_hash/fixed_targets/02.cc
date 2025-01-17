#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" void ge25519_from_hash(char * s, char * h);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need two strings of equal length for the function.
  // We'll divide the input into two parts.
  size_t half_size = size / 2;
  
  // Consume half the bytes for the first string.
  std::string s = stream.ConsumeBytesAsString(half_size);
  
  // Consume the remaining bytes for the second string.
  std::string h = stream.ConsumeRemainingBytesAsString();

  // Ensure both strings are of the same length by padding or truncating.
  if (s.size() < h.size()) {
    h.resize(s.size());
  } else if (h.size() < s.size()) {
    s.resize(h.size());
  }

  // Call the target function.
  ge25519_from_hash(const_cast<char*>(s.c_str()), const_cast<char*>(h.c_str()));

  return 0;
}