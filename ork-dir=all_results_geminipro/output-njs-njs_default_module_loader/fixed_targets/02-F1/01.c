#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <string>

extern "C" {
#include "njs.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t vm_size = stream.ConsumeIntegralInRange<size_t>(1024, 1024 * 1024);
  struct njs_vm_s* vm = njs_create(vm_size);
  if (vm == nullptr) {
    return 0;
  }

  const size_t external_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::string external = stream.ConsumeBytesAsString(external_size);

  const size_t name_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::string name = stream.ConsumeBytesAsString(name_size);
  struct njs_str_t name_str;
  name_str.length = name.size();
  name_str.ptr = reinterpret_cast<uint8_t*>(const_cast<char*>(name.c_str()));

  struct njs_mod_s* mod = njs_default_module_loader(vm, const_cast<char*>(external.c_str()), &name_str);
  if (mod != nullptr) {
    njs_module_destroy(mod);
  }

  njs_destroy(vm);
  return 0;
}