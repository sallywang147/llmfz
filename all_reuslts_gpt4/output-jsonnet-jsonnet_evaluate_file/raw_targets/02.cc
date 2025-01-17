#include <fuzzer/FuzzedDataProvider.h>
#include <libjsonnet.h>
#include <libjsonnet_fmt.h>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct JsonnetVm* vm = jsonnet_make();
  if (vm == nullptr) {
    return 0;
  }

  std::string filename = stream.ConsumeRandomLengthString();
  int error;
  
  char* result = jsonnet_evaluate_file(vm, const_cast<char*>(filename.c_str()), &error);
  
  if (result != nullptr) {
    jsonnet_realloc(vm, result, 0);
  }

  jsonnet_destroy(vm);
  
  return 0;
}