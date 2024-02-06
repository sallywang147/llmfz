#include <fuzzer/FuzzedDataProvider.h>
#include <cstdarg>
#include <cstdint>

#include "x509_ac.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int type = stream.ConsumeIntegral<int>();
  
  // Construct va_list from the fuzzing input
  va_list args;
  va_start(args, type);
  for (size_t i = 0; i < size / sizeof(int); ++i) {
    va_arg(args, int) = stream.ConsumeIntegral<int>();
  }
  va_end(args);

  // Call the target function
  struct x509_ac_t *result = x509_ac_load(type, &args);

  // Free the result
  if (result != nullptr) {
    x509_ac_free(result);
  }

  return 0;
}