#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <libjsonnet.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Jsonnet VM
  JsonnetVm* vm = jsonnet_make();
  if (vm == nullptr) {
    return 0;
  }

  // Extract file name from the fuzzer input
  std::string fileName = stream.ConsumeRandomLengthString();
  char* fileNamePtr = const_cast<char*>(fileName.c_str());

  // Initialize error variable
  int error;

  // Call the target function
  char* result = jsonnet_evaluate_file_multi(vm, fileNamePtr, &error);

  // Cleanup
  jsonnet_realloc(vm, result, 0);
  jsonnet_destroy(vm);

  return 0;
}