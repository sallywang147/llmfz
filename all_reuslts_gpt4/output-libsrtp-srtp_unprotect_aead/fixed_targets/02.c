#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the required structures
  struct srtp_ctx_t_ ctx;
  struct srtp_stream_ctx_t_ srtp_stream;
  struct srtp_session_keys_t session_keys;

  // Consume data from the fuzzer input
  size_t delta = stream.ConsumeIntegral<size_t>();
  size_t est = stream.ConsumeIntegral<size_t>();
  size_t pkt_octet_len = stream.ConsumeIntegral<size_t>();
  size_t mki_size = stream.ConsumeIntegral<size_t>();
  bool advance_packet_index = stream.ConsumeBool();

  // Consume a string for the srtp_hdr
  std::string srtp_hdr_str = stream.ConsumeRemainingBytesAsString();
  char* srtp_hdr = const_cast<char*>(srtp_hdr_str.c_str());

  // Call the target function
  int result = srtp_unprotect_aead(&ctx, &srtp_stream, delta, est, srtp_hdr, &pkt_octet_len, &session_keys, mki_size, advance_packet_index);

  return 0;
}