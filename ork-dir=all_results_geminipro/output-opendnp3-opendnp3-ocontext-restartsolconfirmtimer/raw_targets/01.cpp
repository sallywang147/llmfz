#include <opendnp3/outstation/OContext.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  opendnp3::OContext context;
  context.RestartSolConfirmTimer(nullptr);
  return 0;
}