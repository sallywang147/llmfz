#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "jansson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the data into it.
  FILE* tmp = tmpfile();
  if (!tmp) {
    return 0;
  }
  fwrite(data, sizeof(uint8_t), size, tmp);
  rewind(tmp);

  json_error_t error;
  // Call the target function.
  json_t* json = json_loadf(tmp, 0, &error);

  // Clean up.
  if (json) {
    json_decref(json);
  }
  fclose(tmp);

  return 0;
}