#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jansson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string path = stream.ConsumeRandomLengthString();
  const size_t flags = stream.ConsumeIntegral<size_t>();

  json_error_t error;
  json_t *json = json_load_file(path.c_str(), flags, &error);

  if (json != NULL) {
    json_decref(json);
  }

  return 0;
}