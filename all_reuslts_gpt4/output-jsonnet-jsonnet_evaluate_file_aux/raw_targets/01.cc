#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

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

  // Extract a string from the fuzzed data to use as filename
  std::string filename = provider.ConsumeRandomLengthString();
  int error;
  int multi;

  // Extract a boolean value from the fuzzed data to use as multi
  multi = provider.ConsumeBool();

  // Call the target function
  char* result = jsonnet_evaluate_file_aux(vm, filename.c_str(), &error, multi);

  // Clean up
  jsonnet_realloc(vm, result, 0);
  jsonnet_destroy(vm);

  return 0;
}