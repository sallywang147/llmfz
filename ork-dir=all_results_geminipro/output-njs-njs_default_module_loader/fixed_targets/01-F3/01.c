#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "njs.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string external = stream.ConsumeRemainingBytesAsString();
  struct njs_str_t name;
  name.length = stream.ConsumeIntegral<size_t>();
  name.ptr = const_cast<char*>(external.c_str());
  struct njs_vm_s vm;
  njs_init(&vm, NJS_DEFAULT_FLAGS); // Pass in NJS_DEFAULT_FLAGS as the second argument.
  struct njs_mod_s* mod = njs_default_module_loader(&vm, const_cast<char*>(external.c_str()), &name);
  njs_free_module(&vm, mod);
  njs_free_vm(&vm);
  return 0;
}
```

The issue was that the second argument to `njs_init` was incorrect. It should be `NJS_DEFAULT_FLAGS` instead of `0`.