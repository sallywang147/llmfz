#include <fuzzer/FuzzedDataProvider.h>
#include <boost/json.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int int_arg = stream.ConsumeIntegral<int>();
  int int_arg_in_range = stream.ConsumeIntegralInRange(-100, 100);

  // Extract floating point values
  float probability = stream.ConsumeProbability();
  double double_arg = stream.ConsumeFloatingPoint<double>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char *>(str.c_str());

  // Extract to user defined object
  boost::json::parse_options options;
  options.allow_comments = stream.ConsumeBool();
  options.allow_trailing_commas = stream.ConsumeBool();
  options.allow_invalid_utf8 = stream.ConsumeBool();
  options.max_depth = stream.ConsumeIntegralInRange(0, 100);

  boost::json::value jv;

  try {
    boost::json::parse(jv, ptr, options);
  } catch (...) {
    // Ignore exceptions, as they are expected during fuzzing
  }

  return 0;
}