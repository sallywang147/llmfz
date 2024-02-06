#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "njs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    njs_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  
  // Initialize the VM
  njs_vm_opt_t opt;
  njs_vm_opt_init(&opt);
  njs_vm_t* vm = njs_vm_create(&opt);
  if (vm == nullptr) {
    return 0;
  }

  // Extract the external string
  std::string external_str = provider.ConsumeRandomLengthString();
  char* external = external_str.c_str();

  // Extract the name string
  njs_str_t name;
  std::string name_str = provider.ConsumeRandomLengthString();
  name.start = (u_char*)name_str.c_str();
  name.length = name_str.size();

  // Call the target function
  njs_default_module_loader(vm, external, &name);

  njs_vm_destroy(vm);

  return 0;
}