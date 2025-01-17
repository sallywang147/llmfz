#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  srtp_ctx_t ctx;
  srtp_policy_t policy;
  srtp_stream_ctx_t stream_ctx;
  srtp_session_keys_t session_keys;

  srtp_crypto_kernel_t crypto_kernel = srtp_crypto_kernel_alloc(SRTP_AES_GCM_128_8_AUTH,
                                                                 srtp_crypto_aes_gcm_128_8_auth_get_stream_context);
  srtp_crypto_policy_set_aes_gcm_128_8_auth(&policy.rtp);
  srtp_crypto_policy_set_aes_gcm_128_8_auth(&policy.rtcp);
  srtp_err_status_t status = srtp_create(&ctx, &policy);
  if (status != srtp_err_status_ok) {
    return 0;
  }

  status = srtp_create_stream(&stream_ctx, &ctx);
  if (status != srtp_err_status_ok) {
    return 0;
  }

  size_t delta = stream.ConsumeIntegral<size_t>();
  size_t est = stream.ConsumeIntegral<size_t>();
  size_t mki_size = stream.ConsumeIntegral<size_t>();
  bool advance_packet_index = stream.ConsumeBool();

  std::vector<uint8_t> srtp_hdr(stream.ConsumeIntegralInRange(0, 100));
  std::vector<uint8_t> pkt_octet_len(stream.ConsumeIntegralInRange(0, 100));
  std::vector<uint8_t> session_keys_key(stream.ConsumeIntegralInRange(0, 100));
  std::vector<uint8_t> session_keys_salt(stream.ConsumeIntegralInRange(0, 100));
  std::vector<uint8_t> session_keys_iv(stream.ConsumeIntegralInRange(0, 100));

  memcpy(session_keys.key, session_keys_key.data(), session_keys_key.size());
  memcpy(session_keys.salt, session_keys_salt.data(), session_keys_salt.size());
  memcpy(session_keys.iv, session_keys_iv.data(), session_keys_iv.size());

  status = srtp_unprotect_aead(&ctx, &stream_ctx, delta, est,
                               reinterpret_cast<char*>(srtp_hdr.data()),
                               reinterpret_cast<size_t*>(pkt_octet_len.data()),
                               &session_keys, mki_size, advance_packet_index);
  if (status != srtp_err_status_ok) {
    return 0;
  }

  srtp_dealloc(&ctx);
  return 0;
}
```

The issue is that the `srtp.h` header file is not wrapped in `extern "C" {}` which is necessary for C++ to correctly link with C code. The corrected code includes the header file within `extern "C" {}` to resolve the issue.