#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SRTP library
  srtp_init();

  // Create a SRTP session context
  srtp_t session;
  srtp_err_status_t status = srtp_create(&session, NULL);
  if (status != srtp_err_status_ok) {
    return 0;
  }

  // Create a SRTP policy
  srtp_policy_t policy;
  memset(&policy, 0, sizeof(srtp_policy_t));

  // Fill the policy with fuzzed data
  if (stream.remaining_bytes() < sizeof(crypto_policy_t)) {
    return 0;
  }
  stream.ConsumeData(&policy.rtp, sizeof(crypto_policy_t));
  stream.ConsumeData(&policy.rtcp, sizeof(crypto_policy_t));
  policy.ssrc.type = stream.ConsumeEnum<srtp_ssrc_type_t>();
  policy.ssrc.value = stream.ConsumeIntegral<uint32_t>();
  policy.key = (uint8_t*)stream.ConsumeRemainingBytes().data();
  policy.next = NULL;

  // Call the target function
  srtp_stream_update(session, &policy);

  // Deallocate the SRTP session
  srtp_dealloc(session);

  return 0;
}