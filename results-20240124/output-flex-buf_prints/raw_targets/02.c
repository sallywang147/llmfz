 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "buf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buf_size = stream.ConsumeIntegral<size_t>();
  struct Buf* buf = buf_new(buf_size);
  if (buf == nullptr) {
    return 0;
  }

  const size_t fmt_size = stream.ConsumeIntegral<size_t>();
  char* fmt = static_cast<char*>(malloc(fmt_size + 1));
  if (fmt == nullptr) {
    buf_free(buf);
    return 0;
  }
  stream.ConsumeBytes(fmt, fmt_size);
  fmt[fmt_size] = '\0';

  const size_t s_size = stream.ConsumeIntegral<size_t>();
  char* s = static_cast<char*>(malloc(s_size + 1));
  if (s == nullptr) {
    buf_free(buf);
    free(fmt);
    return 0;
  }
  stream.ConsumeBytes(s, s_size);
  s[s_size] = '\0';

  buf_prints(buf, fmt, s);

  free(fmt);
  free(s);
  buf_free(buf);
  return 0;
}