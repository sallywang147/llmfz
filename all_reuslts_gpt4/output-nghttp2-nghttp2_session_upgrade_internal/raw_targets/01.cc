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

  size_t first_string_size = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  std::string first_string = stream.ConsumeBytesAsString(first_string_size);
  std::string second_string = stream.ConsumeRemainingBytesAsString();

  nghttp2_session_upgrade_internal(session, first_string.data(), first_string.size(), second_string.data());

  nghttp2_session_del(session);

  return 0;
}