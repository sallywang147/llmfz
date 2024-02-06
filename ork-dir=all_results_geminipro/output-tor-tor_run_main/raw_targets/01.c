#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "tor_main.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct tor_main_configuration_t tor_cfg;
  memset(&tor_cfg, 0, sizeof(tor_cfg));
  // TODO(tor-fuzzers): Fuzz more fields.
  tor_cfg.DataDirectory = stream.ConsumeBytesAsString(16).c_str();
  tor_cfg.SocksPort = stream.ConsumeIntegral<uint16_t>();
  tor_cfg.ControlPort = stream.ConsumeIntegral<uint16_t>();
  tor_cfg.CookieAuthFile = stream.ConsumeBytesAsString(16).c_str();
  tor_cfg.Nickname = stream.ConsumeBytesAsString(16).c_str();
  tor_cfg.CircuitBuildTimeout = stream.ConsumeIntegral<int>();
  tor_cfg.CircuitIdleTimeout = stream.ConsumeIntegral<int>();
  tor_cfg.MaxCircuitDirtiness = stream.ConsumeIntegral<int>();
  tor_cfg.ClientOnly = stream.ConsumeBool();
  tor_cfg.UseEntryGuards = stream.ConsumeBool();
  tor_cfg.SafeLogging = stream.ConsumeBool();
  tor_cfg.UseBridges = stream.ConsumeBool();
  tor_cfg.BridgeRelay = stream.ConsumeBytesAsString(16).c_str();
  tor_cfg.BridgeFingerprint = stream.ConsumeBytesAsString(16).c_str();
  tor_cfg.UseDefault = stream.ConsumeBool();
  tor_cfg.AllowInvalidCertificates = stream.ConsumeBool();
  tor_cfg.DisableAllSwap = stream.ConsumeBool();
  tor_cfg.DisablePredictedQueue = stream.ConsumeBool();
  tor_cfg.DisablePredictedCircuit = stream.ConsumeBool();
  tor_cfg.DisablePredictedRelay = stream.ConsumeBool();
  tor_cfg.DisablePredictedGuard = stream.ConsumeBool();
  tor_cfg.DisablePredictedExit = stream.ConsumeBool();
  tor_cfg.DisablePredictedHSDir = stream.ConsumeBool();
  tor_cfg.DisablePredictedRend = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthDir = stream.ConsumeBool();
  tor_cfg.DisablePredictedMicrodesc = stream.ConsumeBool();
  tor_cfg.DisablePredictedConsensus = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthority = stream.ConsumeBool();
  tor_cfg.DisablePredictedNetworkstatus = stream.ConsumeBool();
  tor_cfg.DisablePredictedVote = stream.ConsumeBool();
  tor_cfg.DisablePredictedDescriptor = stream.ConsumeBool();
  tor_cfg.DisablePredictedRelayEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedRelayLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedExitEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedExitLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedGuardEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedGuardLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedHSDirEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedHSDirLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedRendEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedRendLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthDirEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthDirLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedMicrodescEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedMicrodescLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedConsensusEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedConsensusLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthorityEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthorityLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedNetworkstatusEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedNetworkstatusLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedVoteEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedVoteLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedDescriptorEarly = stream.ConsumeBool();
  tor_cfg.DisablePredictedDescriptorLate = stream.ConsumeBool();
  tor_cfg.DisablePredictedRelayEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRelayLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedExitEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedExitLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedGuardEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedGuardLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedHSDirEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedHSDirLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRendEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRendLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthDirEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthDirLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedMicrodescEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedMicrodescLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedConsensusEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedConsensusLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthorityEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthorityLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedNetworkstatusEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedNetworkstatusLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedVoteEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedVoteLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedDescriptorEarly2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedDescriptorLate2 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRelayEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRelayLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedExitEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedExitLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedGuardEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedGuardLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedHSDirEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedHSDirLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRendEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRendLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthDirEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthDirLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedMicrodescEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedMicrodescLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedConsensusEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedConsensusLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthorityEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedAuthorityLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedNetworkstatusEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedNetworkstatusLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedVoteEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedVoteLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedDescriptorEarly3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedDescriptorLate3 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRelayEarly4 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRelayLate4 = stream.ConsumeBool();
  tor_cfg.DisablePredictedExitEarly4 = stream.ConsumeBool();
  tor_cfg.DisablePredictedExitLate4 = stream.ConsumeBool();
  tor_cfg.DisablePredictedGuardEarly4 = stream.ConsumeBool();
  tor_cfg.DisablePredictedGuardLate4 = stream.ConsumeBool();
  tor_cfg.DisablePredictedHSDirEarly4 = stream.ConsumeBool();
  tor_cfg.DisablePredictedHSDirLate4 = stream.ConsumeBool();
  tor_cfg.DisablePredictedRendEarly4 = stream.ConsumeBool();
  tor_cfg.