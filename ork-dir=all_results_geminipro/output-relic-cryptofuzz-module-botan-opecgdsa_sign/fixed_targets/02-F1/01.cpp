#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/module/relic.h"
#include "cryptofuzz/operation/ECDSA_Sign.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> key_bytes = stream.ConsumeBytes<uint8_t>(32);
  std::vector<uint8_t> message_bytes = stream.ConsumeBytes<uint8_t>(32);

  cryptofuzz::module::relic relic_module;
  cryptofuzz::module::Botan botan_module;
  cryptofuzz::operation::ECDSA_Sign ecdsa_sign_operation;

  cryptofuzz::module::Botan::OpECGDSA_Sign(
      nullptr, &relic_module, &ecdsa_sign_operation, key_bytes.data(),
      key_bytes.size(), message_bytes.data(), message_bytes.size());

  return 0;
}
```
The issue was that the header files for the `cryptofuzz` library were not wrapped in `extern "C" {}`. This caused the linker to be unable to find the definitions for the functions and data structures declared in those headers.

To fix the issue, the `extern "C" {}` wrapper was added around the `#include` directives for the `cryptofuzz` headers. This tells the compiler that the declarations in those headers are written in C, not C++. This allows the linker to find the definitions for the functions and data structures when building the program.