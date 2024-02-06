#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t len = stream.ConsumeIntegral<size_t>();
  char* ptr = new char[len];
  size_t ret = pack_dummy(ptr, len);
  delete[] ptr;
  return ret;
}