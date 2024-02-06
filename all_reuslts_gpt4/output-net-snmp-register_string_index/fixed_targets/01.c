#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" char * register_string_index(size_t * name, size_t name_len, char * cp);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    size_t name_len = stream.ConsumeIntegral<size_t>();
    size_t *name = (size_t*) malloc(sizeof(size_t) * name_len);
    if (name == nullptr) {
        return 0;
    }
    for (size_t i = 0; i < name_len; ++i) {
        name[i] = stream.ConsumeIntegral<size_t>();
    }

    std::string str = stream.ConsumeRemainingBytesAsString();
    char *cp = const_cast<char*>(str.c_str());

    char *result = register_string_index(name, name_len, cp);

    free(name);
    return 0;
}