#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/patch_mutation.h"

using firebase::firestore::model::PatchMutation;

extern "C" {
#ifndef __APPLE__
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
#else
int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
#endif
  const char *str_ptr = reinterpret_cast<const char *>(data);
  std::string str{str_ptr, size};

  PatchMutation::Rep rep;
  rep.ToString(&str);
  return 0;
}
}  // extern "C"
```

The build error is caused by the different type definition of `uint8_t` in different platforms. The code above fixes this issue by using `unsigned char` instead of `uint8_t` in the `LLVMFuzzerTestOneInput` function signature.