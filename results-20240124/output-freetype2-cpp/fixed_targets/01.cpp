 #include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Declare and initialize all variables.
  int a = stream.ConsumeIntegral<int>();
  int b = stream.ConsumeIntegral<int>();

  // Call the function to fuzz.
  _GLOBAL__sub_I_template.cpp(a, b);

  return 0;
}