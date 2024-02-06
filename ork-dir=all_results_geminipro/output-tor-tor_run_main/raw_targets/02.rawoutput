#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "tor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tor_main_configuration_t tor_config;
  tor_config.DataDirectory = stream.ConsumeBytesAsString(10).c_str();
  tor_config.CacheDirectory = stream.ConsumeBytesAsString(10).c_str();
  tor_config.GeoIPFile = stream.ConsumeBytesAsString(10).c_str();
  tor_config.GeoIPv6File = stream.ConsumeBytesAsString(10).c_str();
  tor_config.PidFile = stream.ConsumeBytesAsString(10).c_str();
  tor_config.SocksPort = stream.ConsumeIntegral<uint16_t>();
  tor_config.ControlPort = stream.ConsumeIntegral<uint16_t>();
  tor_config.CookieAuthFile = stream.ConsumeBytesAsString(10).c_str();
  tor_config.CookieAuthFileGroupReadable = stream.ConsumeBool();
  tor_config.HashedControlPassword = stream.ConsumeBytesAsString(10).c_str();
  tor_config.HashedControlPassword_len = stream.ConsumeIntegral<uint16_t>();
  tor_config.SafeLogging = stream.ConsumeBool();
  tor_config.LogTimeGranularity = stream.ConsumeIntegral<uint8_t>();
  tor_config.DisableDebuggerAttachment = stream.ConsumeBool();
  tor_config.ClientOnly = stream.ConsumeBool();
  tor_config.BridgeRelay = stream.ConsumeBool();
  tor_config.DirPort = stream.ConsumeIntegral<uint16_t>();
  tor_config.DirPort_set = stream.ConsumeBool();
  tor_config.ExitRelay = stream.ConsumeBool();
  tor_config.PublishServerDescriptor = stream.ConsumeBool();
  tor_config.ContactInfo = stream.ConsumeBytesAsString(10).c_str();
  tor_config.Nickname = stream.ConsumeBytesAsString(10).c_str();
  tor_config.ReachableAddresses = stream.ConsumeBytesAsString(10).c_str();
  tor_config.ReachableDirAddresses =
      stream.ConsumeBytesAsString(10).c_str();
  tor_config.ReachableORAddresses =
      stream.ConsumeBytesAsString(10).c_str();
  tor_config.CircuitIsolationClient = stream.ConsumeBool();
  tor_config.CircuitIsolationPadding = stream.ConsumeBool();
  tor_config.CircuitIsolationExcludeExit = stream.ConsumeBool();
  tor_config.EntryNodes = stream.ConsumeBytesAsString(10).c_str();
  tor_config.ExcludeNodes = stream.ConsumeBytesAsString(10).c_str();
  tor_config.ExcludeExitNodes = stream.ConsumeBytesAsString(10).c_str();
  tor_config.StrictNodes = stream.ConsumeBytesAsString(10).c_str();
  tor_config.DisablePredictedCircuits = stream.ConsumeBool();
  tor_config.MaxCircuitDirtiness = stream.ConsumeIntegral<uint32_t>();
  tor_config.CircuitPathBalance = stream.ConsumeIntegral<uint8_t>();
  tor_config.PathBiasBalance = stream.ConsumeIntegral<uint8_t>();
  tor_config.UseEntryGuards = stream.ConsumeBool();
  tor_config.MaxEntryGuards = stream.ConsumeIntegral<uint8_t>();
  tor_config.NumEntryGuards = stream.ConsumeIntegral<uint8_t>();
  tor_config.EntryGuardIncludeNodes =
      stream.ConsumeBytesAsString(10).c_str();
  tor_config.EntryGuardExcludeNodes =
      stream.ConsumeBytesAsString(10).c_str();
  tor_config.EntryGuardDisablePrivatizeDescriptors =
      stream.ConsumeBool();
  tor_config.EntryGuardHashedDescriptorsOnly = stream.ConsumeBool();
  tor_config.UseEntryGuardsAsDirGuards = stream.ConsumeBool();
  tor_config.FetchDirInfoEarly = stream.ConsumeBool();
  tor_config.FetchUselessDescriptors = stream.ConsumeBool();
  tor_config.FetchGuardDescriptors = stream.ConsumeBool();
  tor_config.FetchServerDescriptors = stream.ConsumeBool();
  tor_config.FetchConsensusDescriptors = stream.ConsumeBool();
  tor_config.FetchAuthorityDescriptors = stream.ConsumeBool();
  tor_config.FetchMicrodescriptors = stream.ConsumeBool();
  tor_config.FetchNetworkstatus = stream.ConsumeBool();
  tor_config.FetchHibernatingDescriptors = stream.ConsumeBool();
  tor_config.DirReqStatistics = stream.ConsumeBool();
  tor_config.TestingTorNetwork = stream.ConsumeBool();
  tor_config.TestingEstimatedBandwidth =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingTorNetwork_AsClient = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsClient =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsServer =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingTorNetwork_AsDirGuard = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsDirGuard =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsExit = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsExit_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsMiddle = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsMiddle_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsBridge = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsBridge_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsV2Dir = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsV2Dir_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsV3Dir = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsV3Dir_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsGuard = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsGuard_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsAuthority = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsAuthority_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsIntroductionPoint =
      stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsIntroductionPoint_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsRouted = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsRouted_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsUnnamed = stream.ConsumeBool();
  tor_config.TestingEstimatedTorNetwork_AsUnnamed_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingTorNetwork_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsClient_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsDirGuard_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsExit_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsMiddle_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsBridge_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_config.TestingEstimatedTorNetwork_AsV2Dir_RelayCellOverhead =
      stream.ConsumeIntegral<uint32_t>();
  tor_