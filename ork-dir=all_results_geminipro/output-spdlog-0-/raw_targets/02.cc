#include <fuzzer/FuzzedDataProvider.h>
#include <fmt/core.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  fmt::v9::basic_memory_buffer<char, 250ul, std::__1::allocator<char>> buffer;
  std::__1::back_insert_iterator<fmt::v9::basic_memory_buffer<char, 250ul, std::__1::allocator<char>>> it(buffer);

  auto format_string = provider.ConsumeRandomLengthString();
  auto args = provider.ConsumeRemainingBytesAsString();

  fmt::v9::vformat_to(it, 0, format_string.size(), format_string.c_str(), args.c_str());

  return 0;
}