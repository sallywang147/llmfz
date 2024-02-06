#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nghttp2/nghttp2.h"

// Callbacks required by nghttp2 library
ssize_t cb_nghttp2_send_callback(nghttp2_session *session, const uint8_t *data,
                                  size_t length, int flags, void *user_data) {
  return length;
}

int cb_nghttp2_on_frame_recv_callback(nghttp2_session *session,
                                      const nghttp2_frame *frame,
                                      void *user_data) {
  return 0;
}

int cb_nghttp2_on_invalid_frame_recv_callback(nghttp2_session *session,
                                              const nghttp2_frame *frame,
                                              uint32_t error_code,
                                              void *user_data) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  nghttp2_session_callbacks *callbacks;
  nghttp2_session_callbacks_new(&callbacks);
  nghttp2_session_callbacks_set_send_callback(callbacks, cb_nghttp2_send_callback);
  nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks, cb_nghttp2_on_frame_recv_callback);
  nghttp2_session_callbacks_set_on_invalid_frame_recv_callback(callbacks, cb_nghttp2_on_invalid_frame_recv_callback);

  nghttp2_session *session;
  nghttp2_session_client_new(&session, callbacks, nullptr);

  FuzzedDataProvider stream(data, size);

  while (stream.remaining_bytes() > 0) {
    const uint8_t* buffer = stream.ConsumeRemainingBytes<uint8_t>().data();
    nghttp2_session_mem_recv(session, buffer, size);
    nghttp2_session_send(session);
  }

  nghttp2_session_del(session);
  nghttp2_session_callbacks_del(callbacks);

  return 0;
}