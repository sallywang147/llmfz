#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "fuzzer-common.h"
#include "fmt/core.h"

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

template <typename T>
void invoke(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto format_str = provider.ConsumeRemainingBytesAsString();
  auto num_args = provider.ConsumeIntegral<size_t>();
  std::vector<fmt::detail::value<T>> args(num_args);
  for (auto& arg : args) {
    arg.type = provider.ConsumeIntegral<fmt::detail::type>();
    arg.int_value = provider.ConsumeIntegral<T>();
  }
  fmt::v10::vprint(stdout, format_str, num_args, 0, args.data());
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size <= 4) return 0;
  const auto representation = data[0];
  data += 1;
  size -= 1;
  switch (representation) {
  case 1:
    invoke<char>(data, size);
    break;
  case 2:
    invoke<signed char>(data, size);
    break;
  case 3:
    invoke<unsigned char>(data, size);
    break;
  case 4:
    invoke<short>(data, size);
    break;
  case 5:
    invoke<unsigned short>(data, size);
    break;
  case 6:
    invoke<int>(data, size);
    break;
  case 7:
    invoke<unsigned int>(data, size);
    break;
  case 8:
    invoke<long>(data, size);
    break;
  case 9:
    invoke<unsigned long>(data, size);
    break;
  case 10:
    invoke<float>(data, size);
    break;
  case 11:
    invoke<double>(data, size);
    break;
  case 12:
    invoke<long double>(data, size);
    break;
  }
  return 0;
}

LIBFUZZER_FUZZER(LLVMFuzzerTestOneInput);