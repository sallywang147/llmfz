#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" void X509dump(char * cert, int ncert);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if(size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string cert = stream.ConsumeBytesAsString(stream.remaining_bytes());

  X509dump(const_cast<char*>(cert.c_str()), cert.size());

  return 0;
}