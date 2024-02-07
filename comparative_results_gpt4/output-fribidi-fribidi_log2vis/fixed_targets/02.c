#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <vector>
#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    const size_t array_size = stream.remaining_bytes() / sizeof(int);
    if (array_size == 0) {
        return 0;
    }

    std::vector<int> str(array_size);
    std::vector<int> visual_str(array_size);
    std::vector<int> positions_L_to_V(array_size);
    std::vector<int> positions_V_to_L(array_size);
    std::vector<char> embedding_levels(array_size);

    for (size_t i = 0; i < array_size; ++i) {
        str[i] = stream.ConsumeIntegral<int>();
    }

    int pbase_dir = stream.ConsumeIntegral<int>();

    fribidi_log2vis(
        str.data(), 
        array_size, 
        &pbase_dir, 
        visual_str.data(), 
        positions_L_to_V.data(), 
        positions_V_to_L.data(), 
        embedding_levels.data()
    );

    return 0;
}