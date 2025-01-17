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

  FuzzedDataProvider stream(data, size);

  // Initialize a VM
  njs_vm_opt_t opt;
  njs_memzero(&opt, sizeof(njs_vm_opt_t));
  njs_vm_t* vm = njs_vm_create(&opt);
  if (vm == nullptr) {
    return 0;
  }

  // Prepare the external string
  std::string external = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  
  // Prepare the name string
  std::string name_str = stream.ConsumeRemainingBytesAsString();
  njs_str_t name;
  name.start = (u_char *) name_str.c_str();
  name.length = name_str.size();

  // Call the target function
  njs_default_module_loader(vm, (char *) external.c_str(), &name);

  // Cleanup
  njs_vm_delete(vm);

  return 0;
}