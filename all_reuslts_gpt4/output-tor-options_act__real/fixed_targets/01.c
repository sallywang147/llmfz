#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "or/or.h"
#include "or/or_options_st.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct or_options_t old_options;

  // Fill the structure with fuzzed data
  old_options.Magic_ = stream.ConsumeIntegral<uint32_t>();
  old_options.CircuitBuildTimeout_ = stream.ConsumeIntegral<int>();
  old_options.CircuitIdleTimeout = stream.ConsumeIntegral<int>();
  old_options.MaxCircuitDirtiness = stream.ConsumeIntegral<int>();
  old_options.NewCircuitPeriod = stream.ConsumeIntegral<int>();
  old_options.__AllDirOptionsPrivate = stream.ConsumeBool();
  old_options.__DisablePredictedCircuits = stream.ConsumeBool();
  old_options.__LeaveStreamsUnattached = stream.ConsumeBool();
  old_options.__OwningControllerProcess = stream.ConsumeIntegral<uint64_t>();
  old_options._AllowInvalid_ = stream.ConsumeIntegral<int>();
  old_options._ClientOnly = stream.ConsumeBool();
  old_options._ExcludeExitNodesUnion_ = stream.ConsumeBool();
  old_options._ExcludeNodes = stream.ConsumeBool();
  old_options._FastFirstHopPK = stream.ConsumeBool();
  old_options._ForceFlags = stream.ConsumeIntegral<int>();
  old_options._NumEntryGuards = stream.ConsumeIntegral<int>();
  old_options._PathsNeededToBuildCircuits = stream.ConsumeIntegral<double>();
  old_options._RefuseUnknownExits = stream.ConsumeBool();
  old_options._SafeLogging = stream.ConsumeIntegral<int>();
  old_options._UseEntryGuards = stream.ConsumeBool();
  old_options._UseMicrodescriptors = stream.ConsumeIntegral<int>();
  old_options._UseNTorHandshake = stream.ConsumeIntegral<int>();
  old_options._UseOnionServices = stream.ConsumeBool();

  // Call the function to fuzz
  int result = options_act__real(&old_options);

  return 0;
}