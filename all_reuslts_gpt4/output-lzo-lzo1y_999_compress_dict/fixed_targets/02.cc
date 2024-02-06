#include <fuzzer/FuzzedDataProvider.h>
#include <lzo/lzo1y.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    FuzzedDataProvider fuzzed_data_provider(data, size);

    // We'll split the data into two parts. One part will be used as the input
    // data to be compressed, and the other part will be used as the dictionary.
    const size_t in_len = fuzzed_data_provider.ConsumeIntegralInRange<size_t>(1, size - 1);
    const size_t dict_len = size - in_len;

    std::string in = fuzzed_data_provider.ConsumeBytesAsString(in_len);
    std::string dict = fuzzed_data_provider.ConsumeRemainingBytesAsString();

    // The output buffer must be at least in_len + in_len / 16 + 64 + 3 bytes.
    size_t out_len = in_len + in_len / 16 + 64 + 3;
    std::vector<char> out(out_len);

    // The working memory must be at least 64 KB.
    std::vector<char> wrkmem(LZO1Y_999_MEM_COMPRESS);

    lzo1y_999_compress_dict(in.data(), in_len, out.data(), &out_len, wrkmem.data(), dict.data(), dict_len);

    return 0;
}