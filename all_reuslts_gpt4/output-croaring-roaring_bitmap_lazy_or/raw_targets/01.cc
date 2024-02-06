#include <fuzzer/FuzzedDataProvider.h>
#include <roaring/roaring.h>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create two roaring bitmaps
    roaring_bitmap_t* bitmap1 = roaring_bitmap_create();
    roaring_bitmap_t* bitmap2 = roaring_bitmap_create();

    // Fill the bitmaps with data
    while (stream.remaining_bytes() > 0) {
        uint32_t value = stream.ConsumeIntegral<uint32_t>();
        roaring_bitmap_add(bitmap1, value);
        value = stream.ConsumeIntegral<uint32_t>();
        roaring_bitmap_add(bitmap2, value);
    }

    // Get a boolean value
    bool lazy = stream.ConsumeBool();

    // Call the target function
    struct roaring_bitmap_s* result = roaring_bitmap_lazy_or(bitmap1, bitmap2, lazy);

    // Clean up
    roaring_bitmap_free(result);
    roaring_bitmap_free(bitmap1);
    roaring_bitmap_free(bitmap2);

    return 0;
}