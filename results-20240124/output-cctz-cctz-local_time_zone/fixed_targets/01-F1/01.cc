#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>
#include <string>

#include "cctz/time_zone.h"

extern "C" {
#include "cctz/time_zone.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    cctz::time_zone::Impl * tz = cctz::local_time_zone();
    return 0;
}