#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jansson.h"

// Define a callback function to be used with json_load_callback
size_t callback(void *buffer, size_t buflen, void *data) {
  FuzzedDataProvider* provider = static_cast<FuzzedDataProvider*>(data);
  if (provider->remaining_bytes() == 0) {
    return 0;  // No more data to provide
  }
  const size_t next_size = provider->ConsumeIntegralInRange<size_t>(0, buflen);
  auto next_input = provider->ConsumeBytes<unsigned char>(next_size);
  memcpy(buffer, next_input.data(), next_input.size());
  return next_input.size();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize error struct
  json_error_t error;

  // Call the function under test
  json_t* json = json_load_callback(callback, (char*)&provider, JSON_REJECT_DUPLICATES, &error);

  if (json != NULL) {
    json_decref(json);
  }

  return 0;
}