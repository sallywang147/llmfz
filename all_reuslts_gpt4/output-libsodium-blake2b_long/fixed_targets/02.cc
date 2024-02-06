#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" int blake2b_long(char * pout, size_t outlen, char * in, size_t inlen);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  const size_t outlen = stream.ConsumeIntegralInRange<size_t>(1, size / 2);
  const size_t inlen = size - outlen;

  std::vector<char> pout(outlen);
  std::vector<char> in(inlen);

  memcpy(in.data(), stream.ConsumeRemainingBytes().data(), inlen);

  blake2b_long(pout.data(), outlen, in.data(), inlen);

  return 0;
}