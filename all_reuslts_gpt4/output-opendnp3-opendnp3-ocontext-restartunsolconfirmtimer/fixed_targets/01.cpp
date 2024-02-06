#include <opendnp3/outstation/OContext.h>
#include <opendnp3/outstation/OutstationContext.h>
#include <opendnp3/outstation/OutstationStackConfig.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for OContext::RestartUnsolConfirmTimer
  opendnp3::OutstationStackConfig config;
  opendnp3::OutstationContext context(config, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
  opendnp3::OContext ocontext(&context);

  // Call the function to fuzz
  ocontext.RestartUnsolConfirmTimer(nullptr);

  return 0;
}