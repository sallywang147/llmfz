#include "cppcheck.h"
#include "type2.h"

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
        FileSettings fs;
        fs.filename = "test.cpp";
        fs.fileContents = std::string(reinterpret_cast<const char*>(data), dataSize); // Fix: change the type of data to const char*
        DummyErrorLogger errorLogger;
        CppCheck cppcheck(errorLogger, false, nullptr);
        cppcheck.settings().addEnabled("all");
        cppcheck.settings().certainty.setEnabled(Certainty::inconclusive, true);
        cppcheck.check(&cppcheck, &fs);
    }
    return 0;
}