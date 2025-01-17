#include "cppcheck.h"
#include "type2.h"

#include <string>
#include <size_t>

enum class Color;

class DummyErrorLogger : public ErrorLogger {
public:
  void reportOut(const std::string & /*outmsg*/, Color /*c*/) override {}
  void reportErr(const ErrorMessage & /*msg*/) override {}
  void reportProgress(const std::string & /*filename*/, const char /*stage*/[], const std::size_t /*value*/) override {} // FN
};

extern "C" {
#include "type2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t dataSize);

std::string generateCode2(const uint8_t *data, size_t dataSize) {
  return std::string(data, dataSize);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t dataSize) {
  if (dataSize < 10000) {
    const std::string code = generateCode2(data, dataSize);

    DummyErrorLogger errorLogger;
    CppCheck cppcheck(errorLogger, false, nullptr);
    cppcheck.settings().addEnabled("all");
    cppcheck.settings().certainty.setEnabled(Certainty::inconclusive, true);
    return cppcheck.check(nullptr, &code);
  }
  return 0;
}