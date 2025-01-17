#include <fuzzer/FuzzedDataProvider.h>
#include <fmt/core.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for parameters
  std::string fmt = stream.ConsumeRandomLengthString();
  size_t args = stream.ConsumeIntegral<size_t>();

  // Create a temporary file to write to
  FILE* f = tmpfile();
  if (f == nullptr) {
    return 0;
  }

  // Create a value array
  fmt::v10::detail::value values[args];
  for (size_t i = 0; i < args; ++i) {
    values[i] = fmt::v10::detail::value(stream.ConsumeIntegral<int>());
  }

  // Call function
  fmt::v10::vprintln(f, fmt.c_str(), args, args, values);

  // Close the temporary file
  fclose(f);

  return 0;
}