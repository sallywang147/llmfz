#include <stddef.h>

#include <openthread/link.h>
#include <openthread/message.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/thread.h>
#include <openthread/thread_ftd.h>

#include "common/code_utils.hpp"
#include "common/time.hpp"
#include "fuzzer_platform.h"
#include "fuzzer_util.h"

using namespace ot;

namespace {

class Joiner : public MeshCoP::Joiner
{
public:
    Joiner(Instance *aInstance) : MeshCoP::Joiner(aInstance) {}

    int Connect(JoinerRouter *aRouter)
    {
        return MeshCoP::Joiner::Connect(this, aRouter);
    }

    void HandleJoinerFinalize(const Message &aMessage, const Ip6::Address &aPeerAddr)
    {
        MeshCoP::Joiner::HandleJoinerFinalize(aMessage, aPeerAddr);
    }

    void HandleJoinerStart(const Message &aMessage, const Ip6::Address &aPeerAddr)
    {
        MeshCoP::Joiner::HandleJoinerStart(aMessage, aPeerAddr);
    }

    void HandleJoinerFinalizeResponse(const Message &aMessage, const Ip6::Address &aPeerAddr)
    {
        MeshCoP::Joiner::HandleJoinerFinalizeResponse(aMessage, aPeerAddr);
    }

    void HandleJoinerStartResponse(const Message &aMessage, const Ip6::Address &aPeerAddr)
    {
        MeshCoP::Joiner::HandleJoinerStartResponse(aMessage, aPeerAddr);
    }

    void HandleJoinerEnergyScanResponse(const Message &aMessage, const Ip6::Address &aPeerAddr)
    {
        MeshCoP::Joiner::HandleJoinerEnergyScanResponse(aMessage, aPeerAddr);
    }

    void HandleJoinerEnergyScan(const Message &aMessage, const Ip6::Address &aPeerAddr)
    {
        MeshCoP::Joiner::HandleJoinerEnergyScan(aMessage, aPeerAddr);
    }
};

class JoinerRouter : public MeshCoP::Joiner::JoinerRouter
{
public:
    JoinerRouter(Instance *aInstance) : MeshCoP::Joiner::JoinerRouter(aInstance) {}

    void HandleJoinerFinalizeRequest(const Message &aMessage, const Ip6::Address &aPeerAddr)
    {
        MeshCoP::Joiner::JoinerRouter::HandleJoinerFinalizeRequest(aMessage, aPeerAddr);
    }

    void HandleJoinerStartRequest(const Message &aMessage, const Ip6::Address &aPeerAddr)
    {
        MeshCoP::Joiner::JoinerRouter::HandleJoinerStartRequest(aMessage, aPeerAddr);
    }

    void HandleJoinerEnergyScanRequest(const Message &aMessage, const Ip6::Address &aPeerAddr)
    {
        MeshCoP::Joiner::JoinerRouter::HandleJoinerEnergyScanRequest(aMessage, aPeerAddr);
    }
};

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    const otPanId panId = 0xdead;

    Instance *instance = nullptr;
    Message *message = nullptr;
    otError error = OT_ERROR_NONE;
    MessageSettings settings;
    Joiner joiner(nullptr);
    JoinerRouter router(nullptr);

    VerifyOrExit(size > 0);

    FuzzerPlatformInit();

    instance = otInstanceInitSingle();
    IgnoreError(otLinkSetPanId(instance, panId));
    IgnoreError(otIp6SetEnabled(instance, true));
    IgnoreError(otThreadSetEnabled(instance, true));
    otSrpServerSetEnabled(instance, true);
    IgnoreError(otThreadBecomeLeader(instance));

    AdvanceTime(instance, 10000);

    settings.mLinkSecurityEnabled = (data[0] & 0x1) != 0;
    settings.mPriority = OT_MESSAGE_PRIORITY_NORMAL;

    message = otIp6NewMessage(instance, &settings);
    VerifyOrExit(message != nullptr, error = OT_ERROR_NO_BUFS);

    error = otMessageAppend(message, data + 1, static_cast<uint16_t>(size - 1));
    SuccessOrExit(error);

    error = otIp6Send(instance, message);

    message = nullptr;

    VerifyOrExit(!FuzzerPlatformResetWasRequested());

    AdvanceTime(instance, 10000);

    joiner.SetRouter(&router);

    joiner.Connect(&router);

    otInstanceFinalize(instance);
    instance = nullptr;

    return 0;
}