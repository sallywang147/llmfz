#include <stddef.h>

#include <openthread/active_scan_result.h>
#include <openthread/coap.h>
#include <openthread/common/code_utils.hpp>
#include <openthread/instance.h>
#include <openthread/joiner.h>
#include <openthread/message.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/platform/radio.h>
#include <openthread/platform/time.h>
#include <openthread/thread.h>
#include <openthread/thread_ftd.h>

#include "common/code_utils.hpp"
#include "common/time.hpp"
#include "fuzzer_platform.h"

namespace ot {
namespace MeshCoP {

class Joiner {
public:
  void HandleDiscoverResult(struct otActiveScanResult *aResult) {
    VerifyOrExit(aResult != nullptr);

    otInstance *instance = otJoinerGetContext(this);
    otMessage *  message = otCoapNewMessage(instance, nullptr);

    VerifyOrExit(message != nullptr, OT_ERROR_NO_BUFS);

    otCoapMessageInit(message, OT_COAP_TYPE_CONFIRMABLE, OT_COAP_CODE_POST);
    otCoapMessageSetPath(message, "/a/as");
    otCoapMessageSetPayloadMarker(message);

    otCoapOptionSetUint16(message, OT_COAP_OPTION_CONTENT_FORMAT, OT_COAP_FORMAT_TLV);
    otCoapOptionSetUint16(message, OT_COAP_OPTION_MAX_AGE, 60);
    otCoapOptionSetUint32(message, OT_COAP_OPTION_BLOCK2, 0);
    otCoapOptionSetUint16(message, OT_COAP_OPTION_SIZE2, 0);

    otCoapSetDefaultHopLimit(message, 255);

    otCoapSetPayload(message, aResult, sizeof(*aResult));

    otMessageSetPeerAddr(message, &aResult->mPeerAddr);

    otMessageSetPeerPort(message, OT_DEFAULT_COAP_PORT);

    otMessageAppend(message, nullptr, 0);

    otCoapSendRequest(instance, message, nullptr);

  exit:

    if (message != nullptr) {
      otMessageFree(message);
    }
  }

  static otJoiner *Get(otInstance *aInstance) { return static_cast<otJoiner *>(otGetUserData(aInstance)); }
};

}  // namespace MeshCoP
}  // namespace ot

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const otPanId panId = 0xdead;

  otInstance *instance = nullptr;
  otMessage *  message = nullptr;
  otError     error   = OT_ERROR_NONE;
  otMessageSettings settings;

  VerifyOrExit(size > 0);

  FuzzerPlatformInit();

  instance = otInstanceInitSingle();
  IgnoreError(otLinkSetPanId(instance, panId));
  IgnoreError(otIp6SetEnabled(instance, true));
  IgnoreError(otThreadSetEnabled(instance, true));
  otSrpServerSetEnabled(instance, true);
  IgnoreError(otThreadBecomeLeader(instance));

  ot::MeshCoP::Joiner joiner;
  otSetUserData(instance, &joiner);

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

exit:

  if (message != nullptr) {
    otMessageFree(message);
  }

  if (instance != nullptr) {
    otInstanceFinalize(instance);
  }

  return 0;
}
}