#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "signkey.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int key_type = stream.ConsumeIntegral<int>();
  const int bits = stream.ConsumeIntegral<int>();
  const std::string filename = stream.ConsumeRemainingBytesAsString();

  signkey_generate(key_type, bits, const_cast<char*>(filename.c_str()), 0);
  return 0;
}