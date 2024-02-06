#include <fuzzer/FuzzedDataProvider.h>
#include <nghttp2/nghttp2.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  nghttp2_session_callbacks* callbacks;
  nghttp2_session_callbacks_new(&callbacks);
  nghttp2_session* session;
  nghttp2_session_server_new(&session, callbacks, nullptr);

  size_t settings_size = stream.ConsumeIntegralInRange<size_t>(0, size/2);
  std::string settings = stream.ConsumeBytesAsString(settings_size);
  int noack = stream.ConsumeIntegral<int>();
  size_t opaque_data_size = stream.remaining_bytes();
  std::string opaque_data = stream.ConsumeRemainingBytesAsString();

  nghttp2_session_upgrade2(session, (uint8_t*)settings.data(), settings.size(), noack, (uint8_t*)opaque_data.data());

  nghttp2_session_del(session);
  nghttp2_session_callbacks_del(callbacks);

  return 0;
}