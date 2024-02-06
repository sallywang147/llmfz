#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "jansson.h"

// Define the callback function
size_t callback(void *buffer, size_t buflen, void *data) {
  FuzzedDataProvider* stream = static_cast<FuzzedDataProvider*>(data);
  const std::vector<uint8_t> bytes = stream->ConsumeBytes<uint8_t>(buflen);
  memcpy(buffer, bytes.data(), bytes.size());
  return bytes.size();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize parameters for json_load_callback
  json_load_callback_t callback_func = callback;
  char* arg = nullptr;
  size_t flags = stream.ConsumeIntegral<size_t>();
  json_error_t error;

  // Call the function to fuzz
  json_t *json = json_load_callback(callback_func, arg, flags, &error);

  // Cleanup
  if (json != nullptr) {
    json_decref(json);
  }

  return 0;
}