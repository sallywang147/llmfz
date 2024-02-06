#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SRTP library
  srtp_init();

  // Create a session
  srtp_t session;
  srtp_policy_t policy;
  
  // Initialize the policy
  srtp_crypto_policy_set_rtp_default(&policy.rtp);
  srtp_crypto_policy_set_rtcp_default(&policy.rtcp);
  policy.ssrc.type  = ssrc_any_outbound;
  policy.ssrc.value = 0;
  policy.key  = (unsigned char *) "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";
  policy.next = NULL;
  
  // Create a SRTP session
  srtp_create(&session, &policy);

  // Update the session with a new policy
  srtp_policy_t new_policy;
  srtp_crypto_policy_set_rtp_default(&new_policy.rtp);
  srtp_crypto_policy_set_rtcp_default(&new_policy.rtcp);
  new_policy.ssrc.type  = ssrc_any_inbound;
  new_policy.ssrc.value = 0;
  new_policy.key  = (unsigned char *) "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";
  new_policy.next = NULL;

  // Call the function to be fuzzed
  stream_update(session, &new_policy);

  // Deallocate session
  srtp_dealloc(session);

  return 0;
}