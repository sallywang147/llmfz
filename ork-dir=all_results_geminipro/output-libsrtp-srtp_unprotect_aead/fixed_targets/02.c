#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "srtp.h"

extern "C" {
#include <libsrtp.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t delta = stream.ConsumeIntegral<size_t>();
  const size_t est = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> srtp_hdr = stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange<size_t>(0, 1024));
  size_t pkt_octet_len = stream.ConsumeIntegral<size_t>();
  const size_t mki_size = stream.ConsumeIntegral<size_t>();
  const bool advance_packet_index = stream.ConsumeBool();

  struct srtp_ctx_t* ctx = srtp_init();
  if (ctx == NULL) {
    return 0;
  }
  struct srtp_stream_ctx_t* stream_ctx = srtp_create_stream(ctx);
  if (stream_ctx == NULL) {
    srtp_dealloc(ctx);
    return 0;
  }

  srtp_unprotect_aead(stream_ctx, delta, est,
                      reinterpret_cast<char*>(srtp_hdr.data()), &pkt_octet_len,
                      nullptr, mki_size, advance_packet_index);

  srtp_dealloc_stream(stream_ctx);
  srtp_dealloc(ctx);

  return 0;
}