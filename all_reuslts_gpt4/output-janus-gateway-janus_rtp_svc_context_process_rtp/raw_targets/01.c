#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "janus_rtp_svc_context.h"
#include "janus_vp9_svc_info.h"
#include "janus_rtp_switching_context.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct janus_rtp_svc_context context;
  struct janus_vp9_svc_info info;
  struct janus_rtp_switching_context sc;

  int vcodec = stream.ConsumeIntegral<int>();

  size_t buf_len = stream.remaining_bytes() / 3;
  std::string buf = stream.ConsumeBytesAsString(buf_len);

  size_t dd_len = stream.remaining_bytes() / 2;
  std::string dd_content = stream.ConsumeBytesAsString(dd_len);

  janus_rtp_svc_context_process_rtp(&context, buf.data(), buf_len, dd_content.data(), dd_len, vcodec, &info, &sc);

  return 0;
}