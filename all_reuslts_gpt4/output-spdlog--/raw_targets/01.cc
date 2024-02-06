#include <fuzzer/FuzzedDataProvider.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/format.h>
#include <spdlog/details/pattern_formatter.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string pattern = stream.ConsumeRandomLengthString();
  std::unique_ptr<spdlog::pattern_formatter> formatter;

  try {
    formatter = spdlog::details::make_unique<spdlog::pattern_formatter>(pattern);
  } catch (...) {
    // spdlog::details::make_unique<spdlog::pattern_formatter> might throw an exception.
    // We catch it here and return early to prevent the fuzzer from crashing.
    return 0;
  }

  return 0;
}