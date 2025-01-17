#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    size_t num_bitmaps = stream.ConsumeIntegralInRange<size_t>(0, 100);
    std::vector<roaring_bitmap_t*> bitmaps(num_bitmaps);

    for (size_t i = 0; i < num_bitmaps; ++i) {
        bitmaps[i] = roaring_bitmap_create();
        size_t num_values = stream.ConsumeIntegralInRange<size_t>(0, 100);
        for (size_t j = 0; j < num_values; ++j) {
            uint32_t value = stream.ConsumeIntegral<uint32_t>();
            roaring_bitmap_add(bitmaps[i], value);
        }
    }

    roaring_bitmap_t* result = roaring_bitmap_xor_many(num_bitmaps, bitmaps.data());

    for (size_t i = 0; i < num_bitmaps; ++i) {
        roaring_bitmap_free(bitmaps[i]);
    }

    roaring_bitmap_free(result);

    return 0;
}