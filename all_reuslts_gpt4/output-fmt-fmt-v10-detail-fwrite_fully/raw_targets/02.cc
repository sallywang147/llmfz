#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t count = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string str = stream.ConsumeBytesAsString(count);
  char* ptr = const_cast<char*>(str.c_str());

  FILE* tmpfile = fopen("/dev/null", "w");
  if (tmpfile == nullptr) {
    return 0;
  }

  fmt::v10::detail::fwrite_fully(ptr, count, tmpfile);

  fclose(tmpfile);

  return 0;
}