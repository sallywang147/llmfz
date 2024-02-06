#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nghttp2/nghttp2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  nghttp2_session_callbacks* callbacks;
  nghttp2_session_callbacks_new(&callbacks);
  nghttp2_session_callbacks_set_send_callback(callbacks, [](nghttp2_session* session, const uint8_t* data, size_t length, int flags, void* user_data) -> ssize_t {
    return length;
  });

  nghttp2_session* session;
  nghttp2_session_client_new(&session, callbacks, nullptr);
  nghttp2_session_callbacks_del(callbacks);

  std::string input = provider.ConsumeRemainingBytesAsString();
  std::string settings = provider.ConsumeBytesAsString(input.size() / 2);
  input = input.substr(input.size() / 2);

  nghttp2_session_upgrade(session, (unsigned char*)settings.c_str(), settings.size(), (char*)input.c_str());

  nghttp2_session_del(session);

  return 0;
}