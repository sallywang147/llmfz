#include <opendnp3/master/StateSolicitedConfirmWait.h>
#include <opendnp3/LogLevels.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <stdexcept>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We don't know the exact structure of opendnp3::OContext and opendnp3::ParsedRequest
  // but we can assume they are POD types for fuzzing purposes.
  // We need to make sure we have enough data for these structures.
  if (stream.remaining_bytes() < sizeof(opendnp3::OContext) + sizeof(opendnp3::ParsedRequest)) {
    return 0;
  }

  // Use FuzzedDataProvider to generate inputs
  std::vector<uint8_t> bad_array_new_length_data = stream.ConsumeBytes<uint8_t>(sizeof(std::bad_array_new_length));
  std::bad_array_new_length* bad_array_new_length_ptr = reinterpret_cast<std::bad_array_new_length*>(bad_array_new_length_data.data());

  std::vector<uint8_t> ocontext_data = stream.ConsumeBytes<uint8_t>(sizeof(opendnp3::OContext));
  opendnp3::OContext* ocontext_ptr = reinterpret_cast<opendnp3::OContext*>(ocontext_data.data());

  std::vector<uint8_t> parsed_request_data = stream.ConsumeBytes<uint8_t>(sizeof(opendnp3::ParsedRequest));
  opendnp3::ParsedRequest* parsed_request_ptr = reinterpret_cast<opendnp3::ParsedRequest*>(parsed_request_data.data());

  // Call the function to fuzz
  opendnp3::StateSolicitedConfirmWait state;
  state.OnNewNonReadRequest(bad_array_new_length_ptr, ocontext_ptr, parsed_request_ptr);

  return 0;
}