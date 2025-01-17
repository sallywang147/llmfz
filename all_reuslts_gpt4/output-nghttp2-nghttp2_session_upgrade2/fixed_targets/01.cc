#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nghttp2/nghttp2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  nghttp2_session_callbacks *callbacks;
  nghttp2_session_callbacks_new(&callbacks);

  nghttp2_session *session;
  nghttp2_session_server_new(&session, callbacks, nullptr);

  FuzzedDataProvider stream(data, size);

  std::string str1 = stream.ConsumeRandomLengthString();
  std::string str2 = stream.ConsumeRemainingBytesAsString();
  int int_arg = stream.ConsumeIntegral<int>();

  nghttp2_session_upgrade2(session, (char *)str1.c_str(), str1.size(), int_arg, (char *)str2.c_str());

  nghttp2_session_del(session);
  nghttp2_session_callbacks_del(callbacks);

  return 0;
}