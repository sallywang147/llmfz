#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

#include "libjsonnet.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static struct JsonnetVm* vm = nullptr;
  if (vm == nullptr) {
    vm = jsonnet_make();
    if (vm == nullptr) {
      return 0;
    }
  }

  FuzzedDataProvider provider(data, size);
  std::string filename = provider.ConsumeRandomLengthString();
  int error;

  char *output = jsonnet_evaluate_file(vm, const_cast<char *>(filename.c_str()), &error);
  if (output == nullptr) {
    return 0;
  }

  jsonnet_realloc(vm, output, 0);  // free the output
  return 0;
}