#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nghttp2/nghttp2.h"

static ssize_t data_source_read_callback(nghttp2_session *session, int32_t stream_id, uint8_t *buf, size_t length, uint32_t *data_flags, nghttp2_data_source *source, void *user_data) {
  FuzzedDataProvider* provider = static_cast<FuzzedDataProvider*>(source->ptr);
  const size_t data_size = provider->ConsumeIntegralInRange<size_t>(0, length);
  std::vector<uint8_t> data = provider->ConsumeBytes<uint8_t>(data_size);
  memcpy(buf, data.data(), data.size());
  if (provider->remaining_bytes() == 0) {
    *data_flags |= NGHTTP2_DATA_FLAG_EOF;
  }
  return data.size();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  nghttp2_session_callbacks* callbacks;
  nghttp2_session_callbacks_new(&callbacks);
  nghttp2_session_callbacks_set_send_callback(callbacks, [](nghttp2_session *session, const uint8_t *data, size_t length, int flags, void *user_data) -> ssize_t {
    return length;
  });

  nghttp2_session* session;
  nghttp2_session_server_new(&session, callbacks, nullptr);
  nghttp2_session_callbacks_del(callbacks);

  nghttp2_data_provider data_provider;
  data_provider.source.ptr = &provider;
  data_provider.read_callback = data_source_read_callback;

  nghttp2_submit_request(session, nullptr, nullptr, 0, &data_provider, nullptr);

  nghttp2_session_recv(session);

  nghttp2_session_del(session);

  return 0;
}