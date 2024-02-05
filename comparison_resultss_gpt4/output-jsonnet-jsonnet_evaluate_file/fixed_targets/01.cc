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

  FuzzedDataProvider provider(data, size);

  struct JsonnetVm* vm = jsonnet_make();
  if (vm == nullptr) {
    return 0;
  }

  std::string file_name = provider.ConsumeRandomLengthString();
  int error;

  char* result = jsonnet_evaluate_file(vm, file_name.c_str(), &error);

  jsonnet_realloc(vm, result, 0);
  jsonnet_destroy(vm);

  return 0;
}