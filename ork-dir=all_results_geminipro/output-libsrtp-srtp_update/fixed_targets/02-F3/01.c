#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t key[SRTP_MAX_KEY_LEN] = {};
  const uint8_t salt[SRTP_MAX_SALT_LEN] = {};
  const uint8_t iv[SRTP_MAX_IV_LEN] = {};
  srtp_policy_t policy = {0};
  policy.key = key;
  policy.key_len = stream.ConsumeIntegralInRange<uint8_t>(0, SRTP_MAX_KEY_LEN);
  policy.salt = salt;
  policy.salt_len = stream.ConsumeIntegralInRange<uint8_t>(0, SRTP_MAX_SALT_LEN);
  policy.iv = iv;
  policy.iv_len = stream.ConsumeIntegralInRange<uint8_t>(0, SRTP_MAX_IV_LEN);
  policy.ssrc.type = stream.ConsumeIntegral<uint8_t>();
  policy.ssrc.value = stream.ConsumeIntegral<uint32_t>();
  policy.window_size = stream.ConsumeIntegral<uint16_t>();
  policy.allow_repeat_tx = stream.ConsumeBool();
  policy.ekt = stream.ConsumeIntegral<uint8_t>();
  policy.auth_tag_len = stream.ConsumeIntegral<uint8_t>();
  policy.cipher_type = stream.ConsumeIntegral<uint8_t>();
  policy.cipher_key_len = stream.ConsumeIntegral<uint8_t>();
  policy.hash_type = stream.ConsumeIntegral<uint8_t>();
  policy.auth_type = stream.ConsumeIntegral<uint8_t>();
  policy.next = nullptr;

  srtp_ctx_t* session = srtp_create(&policy, nullptr);
  if (session == nullptr) {
    return 0;
  }
  srtp_dealloc(session);
  return 0;
}