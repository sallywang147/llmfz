#include <cstddef>
#include <cstdint>

extern "C" {
#include "public/myanmartools.h"
}

using google_myanmar_tools::ZawgyiDetector;

extern "C" int LLVMFuzzerTestOneInput(const