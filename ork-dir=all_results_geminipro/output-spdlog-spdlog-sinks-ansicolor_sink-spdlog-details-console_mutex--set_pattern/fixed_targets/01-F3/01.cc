#include <cstddef>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "spdlog/sinks/ansicolor_sink_mt.h"

extern "C" {
#include "spdlog/spdlog.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string pattern = stream.ConsumeRandomLengthString();

  auto logger = spdlog::create<spdlog::sinks::ansicolor_sink_mt>("fuzzer");
  logger->set_pattern(&pattern);

  return 0;
}