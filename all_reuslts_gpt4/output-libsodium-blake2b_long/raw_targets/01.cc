#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int blake2b_long(char * pout, size_t outlen, char * in, size_t inlen);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  const size_t outlen = stream.ConsumeIntegralInRange<size_t>(0, size);
  char* pout = new char[outlen];
  
  std::string in = stream.ConsumeRemainingBytesAsString();
  
  blake2b_long(pout, outlen, const_cast<char*>(in.c_str()), in.size());
  
  delete[] pout;
  
  return 0;
}