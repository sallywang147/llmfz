#include <fuzzer/FuzzedDataProvider.h>
#include <exception>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::exception *exception = nullptr;
  int *int_ptr = nullptr;

  try {
    piex::(exception, int_ptr);
  } catch (...) {
  }

  return 0;
}