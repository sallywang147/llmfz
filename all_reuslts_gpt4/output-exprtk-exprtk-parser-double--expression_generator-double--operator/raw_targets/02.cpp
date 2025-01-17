#include <cstdint>
#include <string>

#define exprtk_enable_range_runtime_checks
#include "exprtk.hpp"
#include "fuzzer/FuzzedDataProvider.h"

struct timeout_rtc_handler : public exprtk::loop_runtime_check {
  timeout_rtc_handler() : exprtk::loop_runtime_check() {}

  class timeout_exception : public std::runtime_error {
  public:
    timeout_exception(const std::string &what = "") : std::runtime_error(what) {}
  };

  static constexpr std::size_t max_iterations = 5000000;

  using time_point_t = std::chrono::time_point<std::chrono::steady_clock>;

  void set_timeout_time(const time_point_t &timeout_tp) { timeout_tp_ = timeout_tp; }

  bool check() override {
    if (++iterations_ >= max_iterations) {
      if (std::chrono::steady_clock::now() >= timeout_tp_) {
        return false;
      }
      iterations_ = 0;
    }

    return true;
  }

  void handle_runtime_violation(const violation_context &ctx) override { throw timeout_exception("ExprTk Loop run-time timeout violation."); }

  std::size_t iterations_ = 0;
  time_point_t timeout_tp_;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  exprtk::parser<double>::expression_generator<double> generator;
  int int_arg = stream.ConsumeIntegral<int>();
  bool bool_arg = stream.ConsumeBool();

  generator.operator()(&generator, &int_arg, bool_arg);

  return 0;
}