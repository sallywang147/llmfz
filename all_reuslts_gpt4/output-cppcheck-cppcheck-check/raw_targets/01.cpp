#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "cppcheck.h"

class DummyErrorLogger : public ErrorLogger {
public:
  void reportOut(const std::string & /*outmsg*/) override {}
  void reportErr(const ErrorMessage & /*msg*/) override {}
  void reportProgress(const std::string & /*filename*/, const char /*stage*/[], const std::size_t /*value*/) override {}
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string code = stream.ConsumeRemainingBytesAsString();

  DummyErrorLogger errorLogger;
  CppCheck cppcheck(errorLogger, false, nullptr);
  cppcheck.settings().addEnabled("all");
  cppcheck.settings().certainty.setEnabled(Certainty::inconclusive, true);

  cppcheck.check(&cppcheck, &code);

  return 0;
}