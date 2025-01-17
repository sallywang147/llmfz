#include <boost/json.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Extract integral values
  size_t opt = stream.ConsumeIntegral<size_t>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *sp = const_cast<char *>(str.c_str());

  // Extract to user defined object
  boost::json::value s;
  boost::json::storage_ptr storage;
  boost::json::parse_options parseOptions;

  try {
    boost::json::parse(&s, sp, opt, &storage, &parseOptions);
  } catch (...) {
    // Ignore exceptions, we're just fuzzing
  }

  return 0;
}