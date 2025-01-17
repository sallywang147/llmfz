#include <fuzzer/FuzzedDataProvider.h>
#include <optional>
#include "cryptofuzz/operations.h"
#include "cryptofuzz/module.h"
#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/module/BearSSL.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);
    
    cryptofuzz::module::Botan botan_module;
    cryptofuzz::module::BearSSL bearssl_module;
    
    std::optional<std::vector<uint8_t>> privKey = fuzzed_data.ConsumeBytes<uint8_t>(fuzzed_data.ConsumeIntegralInRange<size_t>(0, 32));
    std::optional<std::vector<uint8_t>> nonce = fuzzed_data.ConsumeBytes<uint8_t>(fuzzed_data.ConsumeIntegralInRange<size_t>(0, 32));
    std::optional<std::vector<uint8_t>> cleartext = fuzzed_data.ConsumeBytes<uint8_t>(fuzzed_data.ConsumeIntegralInRange<size_t>(0, 32));
    std::optional<std::vector<uint8_t>> curveType = fuzzed_data.ConsumeBytes<uint8_t>(fuzzed_data.ConsumeIntegralInRange<size_t>(0, 32));
    std::optional<std::vector<uint8_t>> digestType = fuzzed_data.ConsumeBytes<uint8_t>(fuzzed_data.ConsumeIntegralInRange<size_t>(0, 32));
    
    cryptofuzz::operation::ECDSA_Sign ecdsa_sign{std::move(privKey), std::move(nonce), std::move(cleartext), std::move(curveType), std::move(digestType)};
    
    botan_module.OpECGDSA_Sign(nullptr, &bearssl_module, &ecdsa_sign);
    
    return 0;
}