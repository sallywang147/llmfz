#include <cstdint>
#include <cstring>
#include <blake2.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t out_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t in_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* out = new char[out_len];
  char* in = new char[in_len];
  stream.ConsumeBytes(in, in_len);
  blake2b_long(out, out_len, in, in_len);
  delete[] out;
  delete[] in;
  return 0;
}