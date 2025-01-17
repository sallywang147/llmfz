#include <cppcheck.h>
#include <type2.h>
#include "fuzzedDataProvider.h" // Include the missing header file

enum class Color;

class DummyErrorLogger : public ErrorLogger {
public:
    void reportOut(const std::string& /*outmsg*/, Color /*c*/) override {}
    void reportErr(const ErrorMessage& /*msg*/) override {}
    void reportProgress(const std::string& /*filename*/,
                        const char /*stage*/[],
                        const std::size_t /*value*/) override {} // FN
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size); // Use the correct type name
  const std::string code = stream.ConsumeRemainingBytesAsString();
  DummyErrorLogger errorLogger;
  CppCheck cppcheck(errorLogger, false, nullptr);
  cppcheck.settings().addEnabled("all");
  cppcheck.settings().certainty.setEnabled(Certainty::inconclusive, true);
  cppcheck.check("test.cpp", code);
  return 0;
}