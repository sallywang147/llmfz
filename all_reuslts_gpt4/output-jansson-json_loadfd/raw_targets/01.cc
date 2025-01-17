#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jansson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the data into it
  FILE *tmp = tmpfile();
  if (!tmp) {
    return 0;
  }

  fwrite(data, 1, size, tmp);
  rewind(tmp);

  // Get the file descriptor
  int fd = fileno(tmp);

  // Consume data to set the flags
  size_t flags = stream.ConsumeIntegral<size_t>();

  // Call the target function
  json_error_t error;
  json_t *json = json_loadfd(fd, flags, &error);

  // Clean up
  if (json) {
    json_decref(json);
  }

  fclose(tmp);

  return 0;
}