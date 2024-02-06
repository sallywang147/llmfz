#include <utf8proc.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    size_t str_size = stream.ConsumeIntegralInRange<size_t>(0, size);
    std::string str = stream.ConsumeBytesAsString(str_size);
    char* utf8_str = const_cast<char*>(str.c_str());

    int options = stream.ConsumeIntegral<int>();
    size_t buffer_size = stream.remaining_bytes() / sizeof(int);
    std::vector<int> buffer(buffer_size);

    utf8proc_decompose(utf8_str, str_size, buffer.data(), buffer_size, options);

    return 0;
}