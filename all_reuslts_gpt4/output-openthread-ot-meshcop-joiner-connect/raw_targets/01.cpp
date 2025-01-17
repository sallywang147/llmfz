#include <stddef.h>
#include <stdint.h>

#include <openthread/joiner.h>
#include <openthread/thread.h>

#include "common/code_utils.hpp"
#include "fuzzer_platform.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const otPanId panId = 0xdead;

  otInstance *instance = nullptr;
  otError error = OT_ERROR_NONE;
  otJoinerState joinerState;

  FuzzedDataProvider stream(data, size);

  VerifyOrExit(size > 0);

  FuzzerPlatformInit();

  instance = otInstanceInitSingle();
  IgnoreError(otLinkSetPanId(instance, panId));
  IgnoreError(otIp6SetEnabled(instance, true));
  IgnoreError(otThreadSetEnabled(instance, true));

  otJoinerStart(instance, "TEST", "TEST", "TEST", "TEST", "TEST", "TEST", nullptr, nullptr);

  joinerState = otJoinerGetState(instance);

  if (joinerState == OT_JOINER_STATE_IDLE) {
    otJoinerStop(instance);
  }

  ot::MeshCoP::Joiner *joiner = reinterpret_cast<ot::MeshCoP::Joiner *>(instance);
  ot::MeshCoP::Joiner::JoinerRouter router;

  router.mPreference = stream.ConsumeIntegral<int8_t>();
  router.mRloc16 = stream.ConsumeIntegral<uint16_t>();
  router.mPanId = stream.ConsumeIntegral<uint16_t>();
  router.mJoinerUdpPort = stream.ConsumeIntegral<uint16_t>();
  router.mIsJoinable = stream.ConsumeBool();

  int result = joiner->Connect(&router);

exit:

  if (instance != nullptr) {
    otInstanceFinalize(instance);
  }

  return 0;
}