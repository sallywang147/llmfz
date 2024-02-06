#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "njs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct njs_vm_s* vm = njs_vm_create();
  if (vm == nullptr) {
    return 0;
  }

  const std::string module_name = stream.ConsumeRemainingBytesAsString();
  struct njs_str_t name = {module_name.size(),
                           const_cast<char*>(module_name.c_str())};

  const size_t script_size = stream.ConsumeIntegral<size_t>();
  char* script = new char[script_size + 1];
  stream.ConsumeBytes<char>(script, script_size);
  script[script_size] = '\0';

  struct njs_mod_s* module =
      njs_vm_compile_module(vm, &name, &script, script + script_size);
  njs_vm_destroy(vm);
  delete[] script;
  return 0;
}