#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <string>

#include "njs.h"

extern "C" {
#include "njs_compiler.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct njs_vm_s* vm = njs_vm_create();
  if (vm == nullptr) {
    return 0;
  }

  struct njs_str_t name;
  name.length = stream.ConsumeIntegralInRange<uint32_t>(0, 1024);
  name.ptr = static_cast<char*>(malloc(name.length + 1));
  stream.ConsumeBytes(name.ptr, name.length);
  name.ptr[name.length] = '\0';

  const size_t script_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* script = static_cast<char*>(malloc(script_size + 1));
  stream.ConsumeBytes(script, script_size);
  script[script_size] = '\0';

  njs_vm_compile_module(vm, &name, &script, script + script_size);

  free(script);
  free(name.ptr);
  njs_vm_destroy(vm);
  return 0;
}