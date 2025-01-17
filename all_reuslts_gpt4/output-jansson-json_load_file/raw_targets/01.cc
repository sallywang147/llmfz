#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jansson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare a temporary file to write the fuzzed data into.
  char filename[] = "/tmp/fuzzed.json";
  FILE* file = fopen(filename, "wb");
  if (!file) {
    return 0;
  }

  // Write the fuzzed data to the file.
  std::vector<uint8_t> fuzzed_data = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(fuzzed_data.data(), 1, fuzzed_data.size(), file);
  fclose(file);

  // Now, load the file using the function to fuzz.
  json_error_t error;
  json_t* json = json_load_file(filename, 0, &error);

  if (json) {
    json_decref(json);
  }

  // Remove the temporary file.
  remove(filename);

  return 0;
}