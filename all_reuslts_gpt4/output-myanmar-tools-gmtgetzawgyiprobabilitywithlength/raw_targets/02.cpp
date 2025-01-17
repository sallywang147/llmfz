#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "GMTZawgyiDetector.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Initialize the detector
    struct GMTZawgyiDetector *detector = GMTZawgyiDetectorCreate();

    FuzzedDataProvider stream(data, size);
    std::string input_utf8 = stream.ConsumeRemainingBytesAsString();

    // Call the function to fuzz
    double result = GMTGetZawgyiProbabilityWithLength(detector, const_cast<char *>(input_utf8.c_str()), input_utf8.length());

    // Clean up
    GMTZawgyiDetectorDestroy(detector);

    return 0;
}