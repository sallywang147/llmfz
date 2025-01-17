#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include "../readstat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t value = stream.ConsumeIntegral<size_t>();
  size_t variable = stream.ConsumeIntegral<size_t>();

  readstat_variable_t var;
  readstat_value_is_missing(value, variable, &var);

  return 0;
}