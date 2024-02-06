#include <exception>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::exception ex;
  int i = stream.ConsumeIntegral<int>();

  piex::(&ex, &i);

  return 0;
}