#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "janus_rtp_svc_context.h"
#include "janus_vp9_svc_info.h"
#include "janus_rtp_switching_context.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the context
  struct janus_rtp_svc_context context;
  memset(&context, 0, sizeof(context));

  // Initialize the info
  struct janus_vp9_svc_info info;
  memset(&info, 0, sizeof(info));

  // Initialize the switching context
  struct janus_rtp_switching_context sc;
  memset(&sc, 0, sizeof(sc));

  // Get the vcodec
  int vcodec = stream.ConsumeIntegral<int>();

  // Get the length of the buf and dd_content
  size_t buf_len = stream.remaining_bytes() / 2;
  size_t dd_len = stream.remaining_bytes() - buf_len;

  // Get the buf and dd_content
  std::string buf = stream.ConsumeBytesAsString(buf_len);
  std::string dd_content = stream.ConsumeBytesAsString(dd_len);

  // Call the function
  janus_rtp_svc_context_process_rtp(&context, const_cast<char*>(buf.c_str()), buf_len, const_cast<char*>(dd_content.c_str()), dd_len, vcodec, &info, &sc);

  return 0;
}