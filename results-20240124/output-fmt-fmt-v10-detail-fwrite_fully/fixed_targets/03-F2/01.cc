#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fmt/format.h"
#include "fmt/core.h" // Include the header for fwrite_fully

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
  fmt::detail::fwrite_fully(buffer.data(), count, stdout); // Use fmt::detail::fwrite_fully instead
  fmt::print("Wrote {} bytes\n", count);
  return 0;
}