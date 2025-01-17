#include <fuzzer/FuzzedDataProvider.h>
#include "cppcheck.h"

class DummyErrorLogger : public ErrorLogger {
public:
  void reportOut(const std::string & /*outmsg*/) override {}
  void reportErr(const ErrorMessage & /*msg*/) override {}
  void reportProgress(const std::string & /*filename*/, const char /*stage*/[], const std::size_t /*value*/) override {}
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  std::string code = fuzzed_data.ConsumeRemainingBytesAsString();

  DummyErrorLogger errorLogger;
  CppCheck cppcheck(errorLogger, false, nullptr);
  cppcheck.check(&cppcheck, &code);

  return 0;
}