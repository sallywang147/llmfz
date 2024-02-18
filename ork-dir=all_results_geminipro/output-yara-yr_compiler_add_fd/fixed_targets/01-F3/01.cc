#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "yacc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int rules_fd = stream.ConsumeIntegral<int>();
  const std::string namespace_ = stream.ConsumeRemainingBytesAsString();
  const std::string file_name = stream.ConsumeRemainingBytesAsString();

  struct _YR_COMPILER compiler;
  int ret = yr_compiler_add_fd(&compiler, rules_fd,
                               const_cast<char*>(namespace_.c_str()),
                               const_cast<char*>(file_name.c_str()));
  if (ret == 0) {
    yr_compiler_delete(&compiler);
  }
  return 0;
}
```

In this code, the `yr_compiler_add_fd` and `yr_compiler_delete` functions are declared in the `yacc.h` header file, and the `#include "yacc.h"` directive is wrapped with `extern "C" {}`. This fixes the build error.