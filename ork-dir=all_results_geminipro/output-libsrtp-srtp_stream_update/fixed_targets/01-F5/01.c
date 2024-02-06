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
  uint8_t key[SRTP_MAX_KEY_LEN];
  uint8_t salt[SRTP_MAX_SALT_LEN];
  provider.ConsumeBytes<uint8_t>(key, SRTP_MAX_KEY_LEN);
  provider.ConsumeBytes<uint8_t>(salt, SRTP_MAX_SALT_LEN);
  srtp_crypto_policy_set_from_profile_for_test(&policy.rtp, SRTP_AES128_CM_HMAC_SHA1_80);
  srtp_crypto_policy_set_from_profile_for_test(&policy.rtcp, SRTP_AES128_CM_HMAC_SHA1_80);
  srtp_policy_init(&policy);
  srtp_ctx_t session;
  srtp_init();
  srtp_create(&session, &policy);
  srtp_set_master_key(&session, key, SRTP_MAX_KEY_LEN);
  srtp_set_master_salt(&session, salt, SRTP_MAX_SALT_LEN);
  srtp_stream_update(&session, &policy);
  srtp_close(&session);
  srtp_dealloc(&session);
  return 0;
}