#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "nghttp2/nghttp2.h"

static ssize_t send_callback(nghttp2_session* session, const uint8_t* data,
                             size_t length, int flags, void* user_data) {
  return length;
}

static int on_frame_recv_callback(nghttp2_session* session,
                                  const nghttp2_frame* frame, void* user_data) {
  return 0;
}

static int on_data_chunk_recv_callback(nghttp2_session* session, uint8_t flags,
                                       int32_t stream_id, const uint8_t* data,
                                       size_t len, void* user_data) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  nghttp2_session_callbacks* callbacks;
  nghttp2_session_callbacks_new(&callbacks);
  nghttp2_session_callbacks_set_send_callback(callbacks, send_callback);
  nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks,
                                                       on_frame_recv_callback);
  nghttp2_session_callbacks_set_on_data_chunk_recv_callback(
      callbacks, on_data_chunk_recv_callback);

  nghttp2_session* session;
  nghttp2_session_server_new(&session, callbacks, nullptr);
  nghttp2_session_callbacks_del(callbacks);

  nghttp2_settings_entry iv[1] = {{NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS, 100}};
  nghttp2_submit_settings(session, NGHTTP2_FLAG_NONE, iv, 1);

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0, provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<uint8_t>(next_size);
    nghttp2_session_mem_recv(session, next_input.data(), next_input.size());
    nghttp2_session_send(session);
  }

  nghttp2_session_del(session);

  return 0;
}