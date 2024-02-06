#include <stddef.h>
#include <stdint.h>

#include <openthread/instance.h>
#include <openthread/joiner.h>

#include <openthread/thread.h>
#include <openthread/thread_ftd.h>
#include <openthread/platform/radio.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    otInstance *instance = nullptr;

    // Initialize OpenThread instance
    instance = otInstanceInitSingle();
    if (instance == nullptr) {
        return 0;
    }

    // Enable Thread protocol operation
    otThreadSetEnabled(instance, true);

    // Initialize Joiner
    otJoinerPskd pskd;
    ot::MeshCoP::Joiner *joiner = reinterpret_cast<ot::MeshCoP::Joiner *>(otJoinerGetJoiner(instance));

    // Consume data to get the error code
    int aPrevError = stream.ConsumeIntegral<int>();

    // Call the function to be fuzzed
    joiner->TryNextJoinerRouter(aPrevError);

    // Finalize OpenThread instance
    otInstanceFinalize(instance);

    return 0;
}