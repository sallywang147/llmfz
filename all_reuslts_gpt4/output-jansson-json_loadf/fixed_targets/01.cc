#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jansson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Consume data from the fuzzer input
  std::string jsonString = stream.ConsumeRemainingBytesAsString();

  // Create a temporary file and write the data into it
  FILE *fp = tmpfile();
  if (!fp) {
    return 0;
  }
  fwrite(jsonString.data(), 1, jsonString.size(), fp);
  rewind(fp);

  // Call the function with the temporary file
  json_error_t error;
  json_t *json = json_loadf(fp, 0, &error);

  // Clean up
  if (json) {
    json_decref(json);
  }
  fclose(fp);

  return 0;
}