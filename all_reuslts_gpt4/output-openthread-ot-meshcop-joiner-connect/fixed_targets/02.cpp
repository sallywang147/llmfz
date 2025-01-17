#include <stddef.h>
#include <stdint.h>
#include <string>

#include <openthread/instance.h>
#include <openthread/thread.h>
#include <openthread/thread_ftd.h>
#include <openthread/joiner.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    otInstance *instance = nullptr;
    otError error = OT_ERROR_NONE;
    otJoinerState joinerState;

    FuzzedDataProvider stream(data, size);

    instance = otInstanceInitSingle();
    otThreadSetEnabled(instance, true);

    ot::MeshCoP::Joiner *joiner = reinterpret_cast<ot::MeshCoP::Joiner*>(instance);
    ot::MeshCoP::Joiner::JoinerRouter *router = new ot::MeshCoP::Joiner::JoinerRouter();

    error = joiner->Connect(joiner, router);

    otInstanceFinalize(instance);

    return 0;
}