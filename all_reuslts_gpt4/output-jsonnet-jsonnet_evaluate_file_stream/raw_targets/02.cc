#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libjsonnet.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct JsonnetVm* vm = jsonnet_make();
  FuzzedDataProvider provider(data, size);

  // Consume the remaining bytes as a string
  std::string filename = provider.ConsumeRemainingBytesAsString();
  int error;

  // Call the target function
  char* result = jsonnet_evaluate_file_stream(vm, const_cast<char*>(filename.c_str()), &error);

  // Clean up
  jsonnet_realloc(vm, result, 0);
  jsonnet_destroy(vm);

  return 0;
}