#include <stddef.h>
#include <stdint.h>

#include <openthread/instance.h>
#include <openthread/commissioner.h>

#include "common/code_utils.hpp"
#include "fuzzer_platform.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const otPanId panId = 0xdead;
  otInstance *instance = nullptr;
  otError error = OT_ERROR_NONE;

  VerifyOrExit(size > 0);

  FuzzerPlatformInit();

  instance = otInstanceInitSingle();
  IgnoreError(otLinkSetPanId(instance, panId));
  IgnoreError(otIp6SetEnabled(instance, true));
  IgnoreError(otThreadSetEnabled(instance, true));

  otCommissionerStart(instance);

  ot::MeshCoP::Commissioner *commissioner = static_cast<ot::MeshCoP::Commissioner *>(otCommissionerGetInstance(instance));

  commissioner->HandleTimer(commissioner);

exit:

  if (instance != nullptr) {
    otInstanceFinalize(instance);
  }

  return 0;
}