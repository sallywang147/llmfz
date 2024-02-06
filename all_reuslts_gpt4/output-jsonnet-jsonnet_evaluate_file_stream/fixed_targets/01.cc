#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libjsonnet.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize Jsonnet VM
  JsonnetVm* vm = jsonnet_make();

  // Prepare input file as a string
  std::string input_file = provider.ConsumeRemainingBytesAsString();
  char* input_file_cstr = strdup(input_file.c_str());

  // Prepare error flag
  int error;

  // Call the target function
  char* output = jsonnet_evaluate_file_stream(vm, input_file_cstr, &error);

  // Clean up
  free(input_file_cstr);
  jsonnet_realloc(vm, output, 0);
  jsonnet_destroy(vm);

  return 0;
}