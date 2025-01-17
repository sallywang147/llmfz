#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "ZMQCollectorInterface.h"

extern "C" {
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ZMQCollectorInterface* interface = new ZMQCollectorInterface();
  interface->startPacketPolling(interface);
  delete interface;
  return 0;
}
```

In this case, the build error is:

```
error: undefined reference to 'llvm::cl::opt<std::string>'
```

This error is caused by the use of the LLVM command-line library without properly including the necessary headers. To fix this, we need to include the `llvm/Support/CommandLine.h` header and wrap it with `extern "C" {}` to ensure that the C++ compiler generates compatible symbols for linking.

Additionally, we also include the `llvm/Support/raw_ostream.h` header to enable the use of the `llvm::outs()` function for printing messages.