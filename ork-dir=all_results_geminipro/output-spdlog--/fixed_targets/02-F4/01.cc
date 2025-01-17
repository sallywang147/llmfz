#include <cstddef>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
}

std::string my_formatter_txt = "custom-flag";

class my_formatter_flag : public spdlog::custom_flag_formatter {

public:
  void format(const spdlog::details::log_msg &, const std::tm &, spdlog::memory_buf_t &dest) override { dest.append(my_formatter_txt.data(), my_formatter_txt.data() + my_formatter_txt.size()); }

  std::unique_ptr<custom_flag_formatter> clone() const override { return spdlog::details::make_unique<my_formatter_flag>(); }
};

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

  const unsigned long size_arg = stream.ConsumeIntegral<unsigned long>();
  const unsigned long int_arg = stream.ConsumeIntegral<unsigned long>();
  const char flag = (char)(stream.ConsumeIntegral<char>());
  const std::string pattern = stream.ConsumeRandomLengthString();
  my_formatter_txt = stream.ConsumeRandomLengthString();
  const std::string string_arg = stream.ConsumeRandomLengthString();
  const std::string format_string = stream.ConsumeRemainingBytesAsString();

  using spdlog::details::make_unique;
  auto formatter = make_unique<spdlog::pattern_formatter, std::string>(pattern);
  formatter->add_flag<my_formatter_flag>(flag).set_pattern(pattern);
  spdlog::set_formatter(std::move(formatter));

  spdlog::info(format_string.c_str(), size_arg, int_arg, string_arg);

  return 0;
}