#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "srtp.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  srtp_policy_t policy;
  srtp_init();
  srtp_policy_init(&policy);

  // Set SRTP policy parameters.
  policy.ssrc.type = srtp_ssrc_any_type;
  policy.ssrc.value = 0;
  policy.key = provider.ConsumeBytes<uint8_t>(SRTP_MAX_KEY_LEN);
  policy.ekt = provider.ConsumeIntegralInRange<uint8_t>(0, SRTP_MAX_EKT_LEN);
  policy.window_size = provider.ConsumeIntegralInRange<uint16_t>(0, SRTP_MAX_WINDOW_SIZE);
  policy.cipher_type = provider.ConsumeIntegralInRange<uint8_t>(0, SRTP_MAX_CIPHER);
  policy.cipher_key_len = provider.ConsumeIntegralInRange<uint8_t>(0, SRTP_MAX_KEY_LEN);
  policy.auth_type = provider.ConsumeIntegralInRange<uint8_t>(0, SRTP_MAX_AUTH_TYPE);
  policy.auth_key_len = provider.ConsumeIntegralInRange<uint8_t>(0, SRTP_MAX_KEY_LEN);
  policy.auth_tag_len = provider.ConsumeIntegralInRange<uint8_t>(0, SRTP_MAX_TAG_LEN);
  policy.sec_serv = provider.ConsumeIntegralInRange<uint32_t>(0, SRTP_MAX_SEC_SERV);

  // Create a new SRTP session.
  srtp_ctx_t session;
  int ret = srtp_create(&session, &policy);
  if (ret != SRTP_OK) {
    srtp_dealloc(&session);
    return 0;
  }

  // Update the SRTP session.
  ret = srtp_stream_update(&session, &policy);
  if (ret != SRTP_OK) {
    srtp_dealloc(&session);
    return 0;
  }

  // Encrypt and decrypt a message.
  std::vector<uint8_t> plaintext = provider.ConsumeBytes<uint8_t>(1024);
  std::vector<uint8_t> ciphertext(plaintext.size());
  ret = srtp_encrypt(&session, plaintext.data(), plaintext.size(), ciphertext.data());
  if (ret != SRTP_OK) {
    srtp_dealloc(&session);
    return 0;
  }
  std::vector<uint8_t> decryptedtext(plaintext.size());
  ret = srtp_decrypt(&session, ciphertext.data(), ciphertext.size(), decryptedtext.data());
  if (ret != SRTP_OK) {
    srtp_dealloc(&session);
    return 0;
  }

  // Destroy the SRTP session.
  srtp_dealloc(&session);

  return 0;
}