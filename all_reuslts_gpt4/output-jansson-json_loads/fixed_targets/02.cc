#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jansson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  json_error_t error;
  std::string json_string = stream.ConsumeRemainingBytesAsString();
  json_t *json = json_loads(json_string.c_str(), 0, &error);

  if (json != nullptr) {
    json_decref(json);
  }

  return 0;
}