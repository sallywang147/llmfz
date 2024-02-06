#include <fuzzer/FuzzedDataProvider.h>
#include "readstat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract size_t values for value and variable
  size_t value = stream.ConsumeIntegral<size_t>();
  size_t variable = stream.ConsumeIntegral<size_t>();

  // Extract user-defined object
  readstat_variable_t readstat_variable_obj;
  size_t consumed = stream.ConsumeData(&readstat_variable_obj, sizeof(readstat_variable_obj));

  // Call the target function
  int result = readstat_value_is_defined_missing(value, variable, &readstat_variable_obj);

  return 0;
}