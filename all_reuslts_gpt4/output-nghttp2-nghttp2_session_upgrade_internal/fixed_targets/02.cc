#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nghttp2/nghttp2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  nghttp2_session_callbacks* callbacks;
  nghttp2_session_callbacks_new(&callbacks);
  nghttp2_session* session;
  nghttp2_session_server_new(&session, callbacks, nullptr);
  nghttp2_session_callbacks_del(callbacks);

  FuzzedDataProvider provider(data, size);
  
  const size_t first_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  std::string first_str = provider.ConsumeBytesAsString(first_size);
  char *first_input = first_str.c_str();

  const size_t second_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  std::string second_str = provider.ConsumeBytesAsString(second_size);
  char *second_input = second_str.c_str();

  nghttp2_session_upgrade_internal(session, first_input, first_size, second_input);

  nghttp2_session_del(session);

  return 0;
}