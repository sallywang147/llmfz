#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

#include "libjsonnet.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    jsonnet_init();
    initialized = true;
  }

  struct JsonnetVm* vm = jsonnet_make();
  if (vm == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Create a temporary file from the fuzzing input.
  std::string temp_filename = "/tmp/fuzz.jsonnet";
  FILE* temp_file = fopen(temp_filename.c_str(), "wb");
  if (temp_file == nullptr) {
    jsonnet_destroy(vm);
    return 0;
  }

  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
  fwrite(next_input.data(), 1, next_input.size(), temp_file);
  fclose(temp_file);

  int error;
  char* result = jsonnet_evaluate_file_multi(vm, const_cast<char*>(temp_filename.c_str()), &error);

  // Cleanup
  jsonnet_realloc(vm, result, 0);
  jsonnet_destroy(vm);
  remove(temp_filename.c_str());

  return 0;
}