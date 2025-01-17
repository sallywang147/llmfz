#include <fuzzer/FuzzedDataProvider.h>

#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t a_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  size_t b_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  size_t n = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  char* a = new char[a_size + 1];
  char* b = new char[b_size + 1];
  stream.ConsumeBytes(a, a_size);
  stream.ConsumeBytes(b, b_size);
  a[a_size] = '\0';
  b[b_size] = '\0';
  int result = strncmpcanon(a, b, n);
  delete[] a;
  delete[] b;
  return result;
}