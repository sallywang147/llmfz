#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SRTP library
  srtp_init();

  // Create a SRTP session
  srtp_t session;
  srtp_err_status_t status = srtp_create(&session, NULL);
  if (status != srtp_err_status_ok) {
    return 0;
  }

  // Create a SRTP policy
  srtp_policy_t policy;
  memset(&policy, 0, sizeof(policy));

  // Fill the policy with data from the fuzzer
  policy.ssrc.type  = stream.ConsumeEnum<srtp_ssrc_type_t>();
  policy.ssrc.value = stream.ConsumeIntegral<uint32_t>();
  policy.window_size = stream.ConsumeIntegral<uint32_t>();
  policy.allow_repeat_tx = stream.ConsumeBool();
  policy.next = NULL;

  // Call the function to be fuzzed
  int ret = srtp_update(session, &policy);

  // Deallocate the SRTP session
  srtp_dealloc(session);

  return 0;
}