#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "njs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Initialize VM
  njs_vm_opt_t opt;
  njs_vm_opt_init(&opt);
  njs_vm_t* vm = njs_vm_create(&opt);
  if (vm == nullptr) {
    return 0;
  }

  // Prepare name
  njs_str_t name;
  auto name_bytes = provider.ConsumeBytes<char>(1);  // At least one byte for name
  name.start = reinterpret_cast<uint8_t*>(name_bytes.data());
  name.length = name_bytes.size();

  // Prepare script
  std::string script = provider.ConsumeRemainingBytesAsString();
  char* start = const_cast<char*>(script.c_str());
  char* end = start + script.size();

  // Compile module
  njs_mod_t* mod = njs_vm_compile_module(vm, &name, &start, end);

  // Cleanup
  njs_vm_destroy(vm);

  return 0;
}