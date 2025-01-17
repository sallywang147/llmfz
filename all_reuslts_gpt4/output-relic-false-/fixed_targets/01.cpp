#include <fuzzer/FuzzedDataProvider.h>
#include <optional>
#include <botan/ecgdsa.h>
#include <cryptofuzz/operation.h>
#include <cryptofuzz/module.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Prepare the parameters for the function call.
  std::optional<Botan::ECGDSA_PrivateKey> privateKey;
  std::optional<cryptofuzz::operation::ECGDSA_Sign> operation;

  // Consume data from the fuzzed_data to initialize the parameters.
  // Here, we assume that the first byte represents the presence of the privateKey,
  // and the second byte represents the presence of the operation.
  if (fuzzed_data.ConsumeBool()) {
    // Initialize privateKey
    // Here, we just create a default object. In a real fuzzing scenario,
    // you would want to initialize this with meaningful values.
    privateKey.emplace();
  }
  if (fuzzed_data.ConsumeBool()) {
    // Initialize operation
    // Here, we just create a default object. In a real fuzzing scenario,
    // you would want to initialize this with meaningful values.
    operation.emplace();
  }

  // Call the function with the prepared parameters.
  cryptofuzz::module::Botan_detail::ECxDSA_Sign<Botan::ECGDSA_PrivateKey, cryptofuzz::operation::ECGDSA_Sign, false>(&privateKey, &operation);

  return 0;
}