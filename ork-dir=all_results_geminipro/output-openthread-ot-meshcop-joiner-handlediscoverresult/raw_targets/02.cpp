#include <stddef.h>

#include <openthread/active_scan.h>
#include <openthread/coap.h>
#include <openthread/instance.h>
#include <openthread/joiner.h>
#include <openthread/message.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/platform/radio.h>
#include <openthread/platform/time.h>
#include <openthread/thread.h>

#include "common/code_utils.hpp"
#include "common/time.hpp"
#include "fuzzer_platform.h"

void AdvanceTime(otInstance *aInstance, uint32_t aDuration) {
  uint32_t time = otPlatAlarmMilliGetNow() + aDuration;

  while (ot::TimeMilli(otPlatAlarmMilliGetNow()) <= ot::TimeMilli(time)) {
    while (otTaskletsArePending(aInstance)) {
      otTaskletsProcess(aInstance);
    }

    FuzzerPlatformProcess(aInstance);
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const otPanId panId = 0xdead;

  otInstance *instance = nullptr;
  otMessage *message = nullptr;
  otError error = OT_ERROR_NONE;
  otMessageSettings settings;
  otActiveScanResult result;

  VerifyOrExit(size > 0);

  FuzzerPlatformInit();

  instance = otInstanceInitSingle();
  IgnoreError(otLinkSetPanId(instance, panId));
  IgnoreError(otIp6SetEnabled(instance, true));
  IgnoreError(otThreadSetEnabled(instance, true));
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

  result.mChannel = 16;
  result.mPanId = 0xdead;
  result.mVersion = 0;
  result.mNetworkNameLength = 0;
  result.mNetworkName = nullptr;
  result.mIsJoinable = true;
  result.mIsSecure = true;

  ot::MeshCoP::Joiner::HandleDiscoverResult(nullptr, &result);

exit:

  if (message != nullptr) {
    otMessageFree(message);
  }

  if (instance != nullptr) {
    otInstanceFinalize(instance);
  }

  return 0;
}