#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" void init(int, char**);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  const size_t argv_size = stream.ConsumeIntegralInRange<size_t>(1, 10);
  std::vector<char*> argv(argv_size);
  for (size_t i = 0; i < argv_size; i++) {
    const size_t arg_size = stream.ConsumeIntegralInRange<size_t>(1, 10);
    std::vector<uint8_t> arg = stream.ConsumeBytes<uint8_t>(arg_size);
    argv[i] = reinterpret_cast<char*>(arg.data());
  }
  init(argc, argv.data());
  return 0;
}