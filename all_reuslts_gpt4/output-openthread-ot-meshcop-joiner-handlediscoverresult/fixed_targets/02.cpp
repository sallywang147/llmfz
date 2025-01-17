#include <stddef.h>
#include <stdint.h>

#include <openthread/instance.h>
#include <openthread/joiner.h>
#include <openthread/thread.h>

#include "common/code_utils.hpp"
#include "fuzzer_platform.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const otPanId panId = 0xdead;
  otInstance *instance = nullptr;
  otError error = OT_ERROR_NONE;
  otActiveScanResult activeScanResult;
  ot::MeshCoP::Joiner *joiner;

  FuzzerPlatformInit();

  instance = otInstanceInitSingle();
  IgnoreError(otLinkSetPanId(instance, panId));
  IgnoreError(otIp6SetEnabled(instance, true));
  IgnoreError(otThreadSetEnabled(instance, true));
  IgnoreError(otThreadBecomeLeader(instance));

  joiner = reinterpret_cast<ot::MeshCoP::Joiner *>(otJoinerGetJoiner(instance));

  FuzzedDataProvider stream(data, size);

  activeScanResult.mChannel = stream.ConsumeIntegral<uint8_t>();
  activeScanResult.mRssi = stream.ConsumeIntegral<int8_t>();
  activeScanResult.mLqi = stream.ConsumeIntegral<uint8_t>();
  activeScanResult.mVersion = stream.ConsumeIntegral<uint16_t>();
  activeScanResult.mIsJoinable = stream.ConsumeBool();
  activeScanResult.mIsAnnounce = stream.ConsumeBool();

  if (stream.remaining_bytes() > sizeof(activeScanResult.mPanId)) {
    memcpy(&activeScanResult.mPanId, stream.ConsumeBytes<uint8_t>(sizeof(activeScanResult.mPanId)).data(), sizeof(activeScanResult.mPanId));
  }
  if (stream.remaining_bytes() > sizeof(activeScanResult.mExtendedPanId)) {
    memcpy(&activeScanResult.mExtendedPanId, stream.ConsumeBytes<uint8_t>(sizeof(activeScanResult.mExtendedPanId)).data(), sizeof(activeScanResult.mExtendedPanId));
  }
  if (stream.remaining_bytes() > sizeof(activeScanResult.mNetworkName)) {
    memcpy(&activeScanResult.mNetworkName, stream.ConsumeBytes<uint8_t>(sizeof(activeScanResult.mNetworkName)).data(), sizeof(activeScanResult.mNetworkName));
  }
  if (stream.remaining_bytes() > sizeof(activeScanResult.mSteeringData)) {
    memcpy(&activeScanResult.mSteeringData, stream.ConsumeBytes<uint8_t>(sizeof(activeScanResult.mSteeringData)).data(), sizeof(activeScanResult.mSteeringData));
  }

  joiner->HandleDiscoverResult(&activeScanResult);

  otInstanceFinalize(instance);

  return 0;
}