#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t delta = stream.ConsumeIntegral<size_t>();
  const size_t est = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> srtp_hdr = stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange<size_t>(0, 1024));
  size_t pkt_octet_len = stream.ConsumeIntegral<size_t>();
  const size_t mki_size = stream.ConsumeIntegral<size_t>();
  const bool advance_packet_index = stream.ConsumeBool();

  struct srtp_ctx_t_ ctx;
  struct srtp_stream_ctx_t_ stream_ctx;
  struct srtp_session_keys_t session_keys;

  srtp_unprotect_aead(&ctx, &stream_ctx, delta, est,
                      reinterpret_cast<char*>(srtp_hdr.data()), &pkt_octet_len,
                      &session_keys, mki_size, advance_packet_index);

  return 0;
}