#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int save_seed(char * opt);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    std::string str = stream.ConsumeRandomLengthString();
    char *opt = const_cast<char *>(str.c_str());
    save_seed(opt);
    return 0;
}