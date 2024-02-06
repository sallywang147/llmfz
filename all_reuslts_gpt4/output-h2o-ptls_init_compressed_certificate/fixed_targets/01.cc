#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    struct st_ptls_emit_compressed_certificate_t emit_compressed_certificate;
    struct st_h2o_iovec_t iovec;

    // Initialize the parameters
    size_t iovec_len = fuzzed_data.ConsumeIntegral<size_t>();
    char *iovec_base = (char *)fuzzed_data.ConsumeRemainingBytes().data();

    iovec.base = iovec_base;
    iovec.len = iovec_len;

    size_t capacity = fuzzed_data.ConsumeIntegral<size_t>();
    char *base = (char *)fuzzed_data.ConsumeRemainingBytes().data();

    // Call the function with the fuzzed parameters
    int result = ptls_init_compressed_certificate(&emit_compressed_certificate, &iovec, iovec_len, base, capacity);

    return 0;
}