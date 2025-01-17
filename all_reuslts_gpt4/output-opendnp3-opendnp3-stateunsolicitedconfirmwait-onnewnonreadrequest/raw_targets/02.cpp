#include <fuzzer/FuzzedDataProvider.h>
#include <opendnp3/outstation/OContext.h>
#include <opendnp3/outstation/ParsedRequest.h>
#include <opendnp3/outstation/StateUnsolicitedConfirmWait.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the required parameters
  std::bad_array_new_length bad_array_new_length;
  opendnp3::OContext oContext;
  opendnp3::ParsedRequest parsedRequest;

  // Call the function to fuzz
  opendnp3::StateUnsolicitedConfirmWait stateUnsolicitedConfirmWait;
  stateUnsolicitedConfirmWait.OnNewNonReadRequest(&bad_array_new_length, &oContext, &parsedRequest);

  return 0;
}