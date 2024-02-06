#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <fmt/format.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a basic_memory_buffer
  fmt::basic_memory_buffer<char, 250> buffer;

  // Extract values for the vformat_to function
  std::string format_str = stream.ConsumeRandomLengthString();
  size_t arg1 = stream.ConsumeIntegral<size_t>();
  size_t arg2 = stream.ConsumeIntegral<size_t>();

  // Create a fmt::v9::detail::value
  fmt::v9::detail::value val(arg1);

  try {
    fmt::vformat_to(std::back_inserter(buffer), format_str, fmt::make_format_args(val));
  } catch (...) {
    // Ignore any exceptions thrown by the function under test.
  }

  return 0;
}