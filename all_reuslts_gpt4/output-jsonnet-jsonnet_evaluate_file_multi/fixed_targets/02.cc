#include <fuzzer/FuzzedDataProvider.h>
#include <libjsonnet.h>
#include <libjsonnet_fmt.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    jsonnet_max_stack(500);
    jsonnet_gc_min_objects(1000);
    jsonnet_max_trace(20);
    jsonnet_string_output(false);
    initialized = true;
  }

  JsonnetVm* vm = jsonnet_make();
  if (vm == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::string filename = provider.ConsumeRandomLengthString();
  int error;
  char* result = jsonnet_evaluate_file_multi(vm, const_cast<char*>(filename.c_str()), &error);
  if (result != nullptr) {
    jsonnet_realloc(vm, result, 0);
  }

  jsonnet_destroy(vm);

  return 0;
}