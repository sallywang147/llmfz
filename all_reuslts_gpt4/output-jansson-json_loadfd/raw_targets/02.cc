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
  FILE* tmp = tmpfile();
  if (!tmp) {
    return 0;
  }
  fwrite(data, 1, size, tmp);
  rewind(tmp);
  
  // Get the file descriptor of the temporary file
  int fd = fileno(tmp);

  // Consume the flags from the data provider
  size_t flags = stream.ConsumeIntegral<size_t>();

  // Initialize the error struct
  json_error_t error;

  // Call the target function
  json_t* json = json_loadfd(fd, flags, &error);

  // Cleanup
  if (json) {
    json_decref(json);
  }
  fclose(tmp);

  return 0;
}