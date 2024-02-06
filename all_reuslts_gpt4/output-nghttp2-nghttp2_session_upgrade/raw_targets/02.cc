#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nghttp2/nghttp2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  nghttp2_session_callbacks* callbacks;
  nghttp2_session_callbacks_new(&callbacks);
  nghttp2_session* session;
  nghttp2_session_server_new(&session, callbacks, nullptr);
  nghttp2_session_callbacks_del(callbacks);

  size_t settings_len = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes() / 2);
  std::string settings = stream.ConsumeBytesAsString(settings_len);
  std::string client_settings = stream.ConsumeRemainingBytesAsString();

  nghttp2_session_upgrade(session, (uint8_t*)settings.data(), settings.size(), (char*)client_settings.data());

  nghttp2_session_del(session);

  return 0;
}