#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need at least one byte for fmt string and one byte for args
  if (size < 2)
    return 0;

  // Consume 1 byte for fmt string
  std::string fmt = stream.ConsumeBytesAsString(1);
  // Consume 1 byte for args
  size_t args = stream.ConsumeIntegral<size_t>();

  // Prepare FILE pointer
  FILE *f = tmpfile();
  if (!f)
    return 0;

  // Prepare value array
  std::vector<fmt::v10::detail::value> values(args);

  // Call the target function
  fmt::v10::vprintln(f, fmt.c_str(), args, args, values.data());

  // Clean up
  fclose(f);

  return 0;
}