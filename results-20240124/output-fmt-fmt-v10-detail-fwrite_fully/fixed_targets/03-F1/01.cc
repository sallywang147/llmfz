#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fmt/format.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    fmt::print("Initializing\n");
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);
  const size_t count = stream.ConsumeIntegral<size_t>();
  const std::string text = stream.ConsumeRemainingBytesAsString();

  std::vector<char> buffer(count);
  fwrite(buffer.data(), 1, count, stdout); // Use C function fwrite instead
  fmt::print("Wrote {} bytes\n", count);
  return 0;
}