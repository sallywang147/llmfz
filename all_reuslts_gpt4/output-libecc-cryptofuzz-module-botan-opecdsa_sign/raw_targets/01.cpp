#include <fuzzer/FuzzedDataProvider.h>
#include <optional>
#include "cryptofuzz/operations.h"
#include "cryptofuzz/module.h"
#include "cryptofuzz/module/libecc.h"
#include "cryptofuzz/module/botan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzedDataProvider(data, size);

    std::optional<std::string> opt_str;
    if (fuzzedDataProvider.ConsumeBool()) {
        opt_str = fuzzedDataProvider.ConsumeRandomLengthString();
    }

    cryptofuzz::module::libecc libeccModule;
    cryptofuzz::module::Botan botanModule;

    cryptofuzz::operation::ECDSA_Sign op;
    /* Initialize op with data from fuzzedDataProvider */
    /* ... */

    botanModule.OpECDSA_Sign(opt_str, &libeccModule, &op);

    return 0;
}