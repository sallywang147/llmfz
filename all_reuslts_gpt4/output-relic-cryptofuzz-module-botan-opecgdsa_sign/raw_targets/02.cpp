#include <fuzzer/FuzzedDataProvider.h>
#include <optional>
#include <cstddef>
#include <cstdint>

#include "module.h"
#include "operation.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    std::optional<std::string> opt;
    if (stream.ConsumeBool()) {
        opt = stream.ConsumeRandomLengthString();
    }

    cryptofuzz::module::relic relic;
    cryptofuzz::operation::ECDSA_Sign ecdsa_sign;

    cryptofuzz::module::Botan::OpECGDSA_Sign(&opt, &relic, &ecdsa_sign);

    return 0;
}