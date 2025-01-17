#include <stddef.h>
#include <stdint.h>

#include <openthread/joiner.h>
#include <openthread/thread.h>

#include "common/code_utils.hpp"
#include "common/instance.hpp"
#include "fuzzer_platform.h"
#include "meshcop/joiner.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const otPanId panId = 0xdead;

  otInstance *instance = nullptr;
  otError error = OT_ERROR_NONE;
  otActiveScanResult activeScanResult;

  VerifyOrExit(size >= sizeof(activeScanResult));

  FuzzerPlatformInit();

  instance = otInstanceInitSingle();
  IgnoreError(otLinkSetPanId(instance, panId));
  IgnoreError(otIp6SetEnabled(instance, true));
  IgnoreError(otThreadSetEnabled(instance, true));

  ot::Instance *otInstance = static_cast<ot::Instance *>(instance);
  ot::MeshCoP::Joiner &joiner = otInstance->Get<ot::MeshCoP::Joiner>();

  memcpy(&activeScanResult, data, sizeof(activeScanResult));
  joiner.HandleDiscoverResult(&activeScanResult);

exit:

  if (instance != nullptr) {
    otInstanceFinalize(instance);
  }

  return 0;
}