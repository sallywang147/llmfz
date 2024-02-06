#include <fuzzer/FuzzedDataProvider.h>
#include <speex/speex_bits.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider.
    FuzzedDataProvider stream(data, size);

    // Define the size of the float arrays.
    const size_t array_size = 10;
    if (stream.remaining_bytes() < array_size * sizeof(float) * 6 + sizeof(int) * 2) {
        return 0;
    }

    // Initialize float arrays.
    std::vector<float> target = stream.ConsumeBytes<float>(array_size);
    std::vector<float> ak = stream.ConsumeBytes<float>(array_size);
    std::vector<float> awk1 = stream.ConsumeBytes<float>(array_size);
    std::vector<float> awk2 = stream.ConsumeBytes<float>(array_size);
    std::vector<float> exc = stream.ConsumeBytes<float>(array_size);
    std::vector<float> r = stream.ConsumeBytes<float>(array_size);

    // Initialize the rest of the parameters.
    char par = stream.ConsumeIntegral<char>();
    int p = stream.ConsumeIntegral<int>();
    int nsf = stream.ConsumeIntegral<int>();
    SpeexBits bits;
    speex_bits_init(&bits);
    char stack = stream.ConsumeIntegral<char>();
    int complexity = stream.ConsumeIntegral<int>();
    int update_target = stream.ConsumeIntegral<int>();

    // Call the function under test.
    split_cb_search_shape_sign(target.data(), ak.data(), awk1.data(), awk2.data(), &par, p, nsf, exc.data(), r.data(), &bits, &stack, complexity, update_target);

    // Clean up.
    speex_bits_destroy(&bits);

    return 0;
}