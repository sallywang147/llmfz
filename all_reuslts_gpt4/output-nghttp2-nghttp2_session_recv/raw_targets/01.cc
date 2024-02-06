#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nghttp2/nghttp2.h"

extern "C" ssize_t data_prd_read_callback(nghttp2_session *session, int32_t stream_id, uint8_t *buf, size_t length, uint32_t *data_flags, nghttp2_data_source *source, void *user_data) {
  FuzzedDataProvider* stream = static_cast<FuzzedDataProvider*>(source->ptr);
  const auto data = stream->ConsumeBytes<uint8_t>(length);
  if (data.empty()) {
    *data_flags |= NGHTTP2_DATA_FLAG_EOF;
    return 0;
  }
  memcpy(buf, data.data(), data.size());
  return data.size();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  nghttp2_session_callbacks* callbacks;
  nghttp2_session_callbacks_new(&callbacks);
  nghttp2_session_callbacks_set_send_callback(callbacks, [](nghttp2_session *session, const uint8_t *data, size_t length, int flags, void *user_data) {
    return static_cast<ssize_t>(length);
  });
  nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks, [](nghttp2_session *session, const nghttp2_frame *frame, void *user_data) {
    return 0;
  });
  nghttp2_session_callbacks_set_on_data_chunk_recv_callback(callbacks, [](nghttp2_session *session, uint8_t flags, int32_t stream_id, const uint8_t *data, size_t len, void *user_data) {
    return 0;
  });

  nghttp2_session* session;
  nghttp2_session_server_new(&session, callbacks, nullptr);
  nghttp2_session_callbacks_del(callbacks);

  nghttp2_data_provider data_prd;
  data_prd.source.ptr = &stream;
  data_prd.read_callback = data_prd_read_callback;

  nghttp2_submit_request(session, nullptr, nullptr, 0, &data_prd, nullptr);

  nghttp2_session_recv(session);

  nghttp2_session_del(session);

  return 0;
}