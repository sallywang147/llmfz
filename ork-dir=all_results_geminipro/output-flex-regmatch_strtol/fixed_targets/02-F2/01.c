#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <regex.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a regmatch_t struct.
  struct regmatch_t m;
  m.rm_so = stream.ConsumeIntegral<int>();
  m.rm_eo = stream.ConsumeIntegral<int>();

  // Generate a random string.
  std::string str = stream.ConsumeRandomLengthString();
  char* src = str.c_str();

  // Generate a random end pointer.
  char* endptr = src + stream.ConsumeIntegralInRange<size_t>(0, str.size());

  // Generate a random base.
  int base = stream.ConsumeIntegralInRange<int>(2, 37);

  // Call the function.
  regmatch_strtol(&m, src, &endptr, base);

  return 0;
}