#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "janus_rtp_simulcasting.h"
#include "janus_rtp_switching.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct janus_rtp_simulcasting_context context;
  struct janus_rtp_switching_context sc;
  union _GMutex rid_mutex;

  // Initialize the context and switching context
  janus_rtp_simulcasting_context_reset(&context);
  janus_rtp_switching_context_reset(&sc);

  // Consume data for buf and dd_content
  size_t buf_len = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes() / 2);
  std::string buf_str = stream.ConsumeBytesAsString(buf_len);
  char *buf = const_cast<char *>(buf_str.c_str());

  size_t dd_len = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
  std::string dd_str = stream.ConsumeBytesAsString(dd_len);
  char *dd_content = const_cast<char *>(dd_str.c_str());

  // Consume data for ssrcs and rids
  int ssrcs[3] = { stream.ConsumeIntegral<int>(), stream.ConsumeIntegral<int>(), stream.ConsumeIntegral<int>() };
  char *rids[3] = { const_cast<char *>(stream.ConsumeRandomLengthString().c_str()), 
                    const_cast<char *>(stream.ConsumeRandomLengthString().c_str()), 
                    const_cast<char *>(stream.ConsumeRandomLengthString().c_str()) };

  // Consume data for vcodec
  int vcodec = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  janus_rtp_simulcasting_context_process_rtp(&context, buf, buf_len, dd_content, dd_len, ssrcs, rids, vcodec, &sc, &rid_mutex);

  return 0;
}