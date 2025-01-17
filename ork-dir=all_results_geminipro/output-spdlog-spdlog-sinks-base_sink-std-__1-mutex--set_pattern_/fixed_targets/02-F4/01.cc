#include <cstddef>

#include <fuzzer/FuzzedDataProvider.h>

#include "spdlog/sinks/base_sink.h"
#include "spdlog/spdlog.h"

extern "C" {
#include "spdlog/sinks/basic_sink.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  static std::shared_ptr<spdlog::logger> my_logger;
  if (!my_logger.get()) {
    my_logger = spdlog::basic_logger_mt("basic_logger", "/dev/null");
    spdlog::set_default_logger(my_logger);
  }

  FuzzedDataProvider stream(data, size);

  const std::string pattern = stream.ConsumeRandomLengthString();
  spdlog::sinks::base_sink<std::mutex>::set_pattern(my_logger->sinks()[0].get(), pattern);

  spdlog::info("Hello, world!");

  return 0;
}
```

The issue is that the function `spdlog::sinks::base_sink<std::__1::mutex>::set_pattern_(spdlog::sinks::base_sink * , std::string * )` is not called by the fuzz target `LLVMFuzzerTestOneInput`.

The solution is to call the function `spdlog::sinks::base_sink<std::__1::mutex>::set_pattern_(spdlog::sinks::base_sink * , std::string * )` inside the function `LLVMFuzzerTestOneInput`.

The fixed code is shown above.