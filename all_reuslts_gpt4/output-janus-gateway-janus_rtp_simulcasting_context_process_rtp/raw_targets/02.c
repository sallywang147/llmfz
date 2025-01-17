#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "janus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct janus_rtp_simulcasting_context context;
  struct janus_rtp_switching_context sc;
  union _GMutex rid_mutex;
  int vcodec = stream.ConsumeIntegral<int>();
  int ssrcs[3] = {stream.ConsumeIntegral<int>(), stream.ConsumeIntegral<int>(), stream.ConsumeIntegral<int>()};
  char *rids[3] = {nullptr, nullptr, nullptr};

  size_t buf_len = stream.remaining_bytes() / 2;
  std::string buf = stream.ConsumeBytesAsString(buf_len);
  size_t dd_len = stream.remaining_bytes();
  std::string dd_content = stream.ConsumeRemainingBytesAsString();

  janus_rtp_simulcasting_context_reset(&context);
  janus_rtp_switching_context_reset(&sc);

  janus_rtp_simulcasting_context_process_rtp(&context, buf.data(), buf.size(), dd_content.data(), dd_content.size(), ssrcs, rids, vcodec, &sc, &rid_mutex);

  return 0;
}