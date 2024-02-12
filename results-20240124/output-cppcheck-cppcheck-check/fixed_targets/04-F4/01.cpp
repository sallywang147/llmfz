#include "cppcheck.h"
#include "type2.h"
#include "analyzerinfo.h" // Include the header that defines FileSettings

enum class Color;

class DummyErrorLogger : public ErrorLogger {
public:
    void reportOut(const std::string& /*outmsg*/, Color /*c*/) override {}
    void reportErr(const ErrorMessage& /*msg*/) override {}
    void reportProgress(const std::string& /*filename*/,
                        const char /*stage*/[],
                        const std::size_t /*value*/) override {} // FN
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t dataSize);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t dataSize)
{
    if (dataSize < 10000) {
        const std::string code = generateCode2(data, dataSize);

        DummyErrorLogger errorLogger;
        CppCheck cppcheck(errorLogger, false, nullptr);
        cppcheck.settings().addEnabled("all");
        cppcheck.settings().certainty.setEnabled(Certainty::inconclusive, true);

        FileSettings fileSettings; // Now the definition of FileSettings is included
        cppcheck.check(&cppcheck, &fileSettings);
    }
    return 0;
}