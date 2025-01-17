#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libjsonnet++.h"

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

  int error = 0;
  int flags = provider.ConsumeIntegral<int>();

  std::string filename = provider.ConsumeRandomLengthString();
  char* result = jsonnet_evaluate_file_aux(vm, const_cast<char*>(filename.c_str()), &error, flags);

  if (result != nullptr) {
    jsonnet_realloc(vm, result, 0);
  }

  jsonnet_destroy(vm);

  return 0;
}