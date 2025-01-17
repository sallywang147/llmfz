#include <fuzzer/FuzzedDataProvider.h>
#include <Poco/RegularExpression.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    FuzzedDataProvider fuzzedDataProvider(data, size);

    std::string input = fuzzedDataProvider.ConsumeRandomLengthString();
    std::string pattern = fuzzedDataProvider.ConsumeRemainingBytesAsString();

    Poco::RegularExpression re(pattern);
    std::vector<std::string> result;

    try {
        re.split(input, 0, result);
    } catch (Poco::RegularExpressionException &e) {
        return 0;
    }

    return 0;
}