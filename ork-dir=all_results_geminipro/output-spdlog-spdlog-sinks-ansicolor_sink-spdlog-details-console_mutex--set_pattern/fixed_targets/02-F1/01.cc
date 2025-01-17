#include <cstddef>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>

#include "spdlog/sinks/ansicolor_sink.h"

extern "C" {
#include "spdlog/spdlog.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  const std::string pattern = stream.ConsumeRandomLengthString();

  spdlog::sinks::ansicolor_sink<spdlog::details::console_mutex> sink;
  sink.set_pattern(&sink, &pattern);

  return 0;
}
```

In this code, the issue is that the `spdlog` header is not wrapped with `extern "C" {}`. This causes the linker to not be able to find the `spdlog` functions when linking the object file. To fix this, we wrap the `spdlog` header with `extern "C" {}`.