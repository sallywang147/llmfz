#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize srtp library
  srtp_init();

  // Initialize session
  srtp_ctx_t_ session;
  memset(&session, 0, sizeof(session));

  // Initialize policy
  srtp_policy_t policy;
  memset(&policy, 0, sizeof(policy));

  // Consume data for policy
  policy.ssrc.type  = stream.ConsumeEnum<srtp_ssrc_type_t>();
  policy.ssrc.value = stream.ConsumeIntegral<uint32_t>();
  policy.window_size = stream.ConsumeIntegral<uint32_t>();
  policy.allow_repeat_tx = stream.ConsumeBool();

  // Consume data for session
  session.enc_algo = stream.ConsumeEnum<srtp_cipher_type_id_t>();
  session.auth_algo = stream.ConsumeEnum<srtp_auth_type_id_t>();
  session.rtp_auth_tag_len = stream.ConsumeIntegral<uint8_t>();
  session.rtcp_auth_tag_len = stream.ConsumeIntegral<uint8_t>();

  // Call the target function
  update_template_streams(&session, &policy);

  return 0;
}