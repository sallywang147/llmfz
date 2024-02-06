#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <locale>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int c = stream.ConsumeIntegral<int>();
  std::iscntrl(c);
  std::isascii(c); // Add this line
  return 0;
}