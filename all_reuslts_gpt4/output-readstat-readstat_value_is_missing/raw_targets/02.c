#include <fuzzer/FuzzedDataProvider.h>
#include "readstat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(readstat_variable_t)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Extract the value and variable from the stream
  size_t value = stream.ConsumeIntegral<size_t>();
  size_t variable = stream.ConsumeIntegral<size_t>();

  // Extract a readstat_variable_t object from the stream
  readstat_variable_t var_obj;
  size_t consumed = stream.ConsumeData(&var_obj, sizeof(var_obj));

  // If we didn't consume enough data for a valid readstat_variable_t, return
  if (consumed != sizeof(readstat_variable_t)) {
    return 0;
  }

  // Call the function to fuzz
  int result = readstat_value_is_missing(value, variable, &var_obj);

  return 0;
}