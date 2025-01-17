#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include "ots.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create two SILSub objects
    ots::OpenTypeSILF::SILSub silsub1;
    ots::OpenTypeSILF::SILSub silsub2;

    // Consume data to fill the first SILSub object
    size_t consumed = stream.ConsumeData(&silsub1, sizeof(silsub1));

    // If there is still data left, consume it to fill the second SILSub object
    if (stream.remaining_bytes() > 0) {
        consumed = stream.ConsumeData(&silsub2, sizeof(silsub2));
    }

    // Call the SILSub function
    silsub1.SILSub(&silsub2);

    return 0;
}