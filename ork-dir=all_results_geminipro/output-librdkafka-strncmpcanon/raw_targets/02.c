#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t max_str_size = 1024;
  char str1[max_str_size];
  char str2[max_str_size];

  size_t str1_size = stream.ConsumeIntegralInRange<size_t>(0, max_str_size);
  size_t str2_size = stream.ConsumeIntegralInRange<size_t>(0, max_str_size);

  stream.ConsumeBytes(str1, str1_size);
  stream.ConsumeBytes(str2, str2_size);

  int cmp_size = stream.ConsumeIntegralInRange<int>(0, max_str_size);

  strncmpcanon(str1, str2, cmp_size);

  return 0;
}