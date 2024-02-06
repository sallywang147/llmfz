#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SRTP library
  srtp_init();

  // Create a SRTP context
  srtp_ctx_t_ *session;
  srtp_create(&session, NULL);

  // Create a SRTP policy
  srtp_policy_t policy;
  memset(&policy, 0, sizeof(policy));

  // Consume data for the policy key
  std::vector<uint8_t> key = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes());
  policy.key = key.data();

  // Call the target function
  int result = srtp_update(session, &policy);

  // Clean up
  srtp_dealloc(session);

  return 0;
}