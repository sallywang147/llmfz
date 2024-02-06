#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);
    size_t numBitmaps = stream.ConsumeIntegralInRange<size_t>(1, 100);
    std::vector<struct roaring_bitmap_s*> bitmaps(numBitmaps);

    for(size_t i = 0; i < numBitmaps; ++i) {
        bitmaps[i] = roaring_bitmap_create();
        size_t numValues = stream.ConsumeIntegralInRange<size_t>(0, 1000);
        for(size_t j = 0; j < numValues; ++j) {
            uint32_t value = stream.ConsumeIntegral<uint32_t>();
            roaring_bitmap_add(bitmaps[i], value);
        }
    }

    struct roaring_bitmap_s* result = roaring_bitmap_or_many(numBitmaps, bitmaps.data());

    for(size_t i = 0; i < numBitmaps; ++i) {
        roaring_bitmap_free(bitmaps[i]);
    }
    roaring_bitmap_free(result);

    return 0;
}