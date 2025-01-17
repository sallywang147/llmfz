#include <fuzzer/FuzzedDataProvider.h>
#include <spdlog/details/pattern_formatter.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string pattern = stream.ConsumeRandomLengthString();
  std::unique_ptr<spdlog::pattern_formatter> formatter;

  formatter = spdlog::details::make_unique<spdlog::pattern_formatter, const std::string&>(&formatter, &pattern);

  return 0;
}