#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "njs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the VM
  njs_vm_opt_t opt;
  njs_vm_opt_init(&opt);
  njs_vm_t* vm = njs_vm_create(&opt);
  if (vm == nullptr) {
    return 0;
  }

  // Prepare the input for njs_vm_compile_module
  std::string input = stream.ConsumeRemainingBytesAsString();
  char* start = const_cast<char*>(input.c_str());
  char* end = start + input.size();

  // Define a module name
  njs_str_t name;
  name.start = reinterpret_cast<u_char*>("fuzzed_module");
  name.length = strlen(reinterpret_cast<char*>(name.start));

  // Call the function to fuzz
  njs_mod_t* mod = njs_vm_compile_module(vm, &name, &start, end);

  // Cleanup
  if (mod != nullptr) {
    njs_vm_module_remove(vm, mod);
  }
  njs_vm_destroy(vm);

  return 0;
}