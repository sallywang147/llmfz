#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "rar.hpp"

extern "C" {
#include "rar.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    rar::rar_init();
    initialized = true;
  }

  rar::Archive archive;
  rar::CmdExtract cmd;

  std::vector<uint8_t> output_buffer(1024 * 1024);

  FuzzedDataProvider provider(data, size);
  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
  if (!archive.Open(next_input.data(), next_input.size())) {
    return 0;
  }

  archive.CheckArc(true);

  return 0;
}
```

The provided code has no build issues. Therefore, there is no need to fix it.