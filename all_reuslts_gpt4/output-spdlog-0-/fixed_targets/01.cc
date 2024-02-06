#include <fuzzer/FuzzedDataProvider.h>

#include <fmt/core.h>
#include <fmt/format.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string format_string = stream.ConsumeRandomLengthString();
  char* format_str = const_cast<char*>(format_string.c_str());

  std::vector<fmt::v9::detail::value> values;
  while (stream.remaining_bytes() > 0) {
    int type = stream.ConsumeIntegralInRange<int>(0, 2);
    switch (type) {
      case 0:
        values.push_back(fmt::v9::detail::make_arg<fmt::v9::detail::type::int_type>(stream.ConsumeIntegral<int>()));
        break;
      case 1:
        values.push_back(fmt::v9::detail::make_arg<fmt::v9::detail::type::double_type>(stream.ConsumeFloatingPoint<double>()));
        break;
      case 2:
        values.push_back(fmt::v9::detail::make_arg<fmt::v9::detail::type::cstring_type>(stream.ConsumeRandomLengthString().c_str()));
        break;
    }
  }

  fmt::v9::basic_memory_buffer<char, 250ul, std::__1::allocator<char>> buf;
  try {
    fmt::v9::vformat_to(std::__1::back_inserter(buf), format_str, fmt::v9::format_args(values.data(), values.size()));
  } catch (fmt::v9::format_error&) {
    // Ignore formatting errors.
  }

  return 0;
}