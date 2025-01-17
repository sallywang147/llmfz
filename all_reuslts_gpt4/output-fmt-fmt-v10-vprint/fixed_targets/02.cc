#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare a FILE* for vprint to write to. We don't actually care about the
  // output, so it writes to /dev/null.
  FILE* f = fopen("/dev/null", "w");
  if (!f) {
    return 0;
  }

  // Consume some data for the format string. We consume a relatively small
  // amount of data for this because format strings are generally small and we
  // want to leave data for the arguments.
  std::string format = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);

  // Prepare some arguments for the format string. The contents don't matter
  // much as we're just trying to trigger potential issues in vprint. We just
  // create a bunch of arguments with random data.
  std::vector<fmt::v10::detail::value> args;
  while (stream.remaining_bytes() > 0) {
    // Create a value with a random int.
    int i = stream.ConsumeIntegral<int>();
    args.push_back(fmt::v10::detail::value(i));
  }

  // Call vprint with the format string and arguments.
  fmt::v10::vprint(f, format.c_str(), fmt::v10::format_args(args.data(), args.size(), args.size()));

  fclose(f);

  return 0;
}