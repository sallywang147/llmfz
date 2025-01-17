#include <opendnp3/outstation/OContext.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  opendnp3::OContext context;
  // The function argument type is anonymous, so we will use a pointer to void
  void* arg = nullptr;

  context.RestartUnsolConfirmTimer(arg);

  return 0;
}