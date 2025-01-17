#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const uint8_t key[SRTP_MAX_KEY_LEN] = {};
  const uint8_t salt[SRTP_MAX_SALT_LEN] = {};
  const srtp_cipher_type_t cipher = stream.PickValueInArray(
      {SRTP_NULL_CIPHER, SRTP_AES_ICM_128, SRTP_AES_ICM_256});
  const srtp_auth_type_t auth = stream.PickValueInArray(
      {SRTP_NULL_AUTH, SRTP_HMAC_SHA1, SRTP_HMAC_SHA256});
  const uint32_t ssrc = stream.ConsumeIntegral<uint32_t>();
  const uint32_t window_size = stream.ConsumeIntegral<uint32_t>();
  const uint32_t lifetime = stream.ConsumeIntegral<uint32_t>();
  const uint32_t flags = stream.ConsumeIntegral<uint32_t>();

  srtp_policy_t policy = {0};
  srtp_policy_set_key(&policy, key, sizeof(key));
  srtp_policy_set_salt(&policy, salt, sizeof(salt));
  srtp_policy_set_cipher(&policy, cipher);
  srtp_policy_set_auth_type(&policy, auth);
  srtp_policy_set_ssrc(&policy, ssrc);
  srtp_policy_set_window_size(&policy, window_size);
  srtp_policy_set_lifetime(&policy, lifetime);
  srtp_policy_set_flags(&policy, flags);

  srtp_ctx_t_ session = {0};
  int ret = srtp_create(&session, &policy);
  if (ret != SRTP_OK) {
    return 0;
  }

  ret = stream_update(&session, &policy);
  if (ret != SRTP_OK) {
    srtp_dealloc(&session);
    return 0;
  }

  srtp_dealloc(&session);
  return 0;
}