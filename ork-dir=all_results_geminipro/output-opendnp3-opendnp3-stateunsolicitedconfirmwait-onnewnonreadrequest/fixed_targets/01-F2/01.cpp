#include <stddef.h>

#include <opendnp3/master/StateUnsolicitedConfirmWait.h>
#include <opendnp3/master/MasterOperations.h>

#include <dnp3mocks/MockOContext.h>
#include <dnp3mocks/MockParsedRequest.h>

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  opendnp3::StateUnsolicitedConfirmWait state;
  std::bad_array_new_length array;
  opendnp3::MockOContext context;
  opendnp3::MockParsedRequest request;

  state.OnNewNonReadRequest(&array, &context, &request);
  return 0;
}
}