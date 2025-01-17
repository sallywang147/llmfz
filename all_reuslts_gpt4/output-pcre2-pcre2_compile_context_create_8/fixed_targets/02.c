#include <fuzzer/FuzzedDataProvider.h>
#include <pcre2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzedDataProvider(data, size);

    pcre2_general_context *generalContext = pcre2_general_context_create(NULL, NULL, NULL);
    if (!generalContext) {
        return 0;
    }

    pcre2_compile_context *compileContext = pcre2_compile_context_create(generalContext);
    if (!compileContext) {
        pcre2_general_context_free(generalContext);
        return 0;
    }

    pcre2_compile_context_free(compileContext);
    pcre2_general_context_free(generalContext);

    return 0;
}