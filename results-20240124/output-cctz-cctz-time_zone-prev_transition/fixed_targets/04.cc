#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/civil_time.h"
#include "cctz/time_zone.h"

extern "C" {
#include "cctz/time_zone.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    cctz::time_zone lax;
    std::string tz = fuzzed_data.ConsumeRandomLengthString();
    if (load_time_zone(tz, &lax)) {
        std::chrono::system_clock::time_point tp;
        cctz::time_point<cctz::seconds> cctz_tp = cctz::convert(cctz::civil_second(tp.time_since_epoch()), lax);
        cctz::time_zone::civil_transition trans;
        lax.prev_transition(cctz_tp, &trans);
    }

    return 0;
}
}