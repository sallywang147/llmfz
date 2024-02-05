#include <fuzzer/FuzzedDataProvider.h>
#include <libjsonnet.h>
#include <libjsonnet_fmt.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    struct JsonnetVm *vm;
    int error;
    char *output;

    vm = jsonnet_make();
    std::string filename = stream.ConsumeRandomLengthString();
    output = jsonnet_evaluate_file_multi(vm, const_cast<char*>(filename.c_str()), &error);

    if (output == nullptr) {
        fprintf(stderr, "Error: %s\n", jsonnet_realloc_get_error(vm));
        jsonnet_destroy(vm);
        return 1;
    }

    jsonnet_realloc_free(vm, output);
    jsonnet_destroy(vm);
    return 0;
}