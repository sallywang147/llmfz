#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct srtp_ctx_t_ ctx;
  struct srtp_stream_ctx_t_ stream_ctx;
  struct srtp_session_keys_t session_keys;

  size_t delta = stream.ConsumeIntegral<size_t>();
  size_t est = stream.ConsumeIntegral<size_t>();
  size_t pkt_octet_len = stream.ConsumeIntegral<size_t>();
  size_t mki_size = stream.ConsumeIntegral<size_t>();
  bool advance_packet_index = stream.ConsumeBool();

  std::string srtp_hdr = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  srtp_unprotect_aead(&ctx, &stream_ctx, delta, est, srtp_hdr.data(), &pkt_octet_len, &session_keys, mki_size, advance_packet_index);

  return 0;
}