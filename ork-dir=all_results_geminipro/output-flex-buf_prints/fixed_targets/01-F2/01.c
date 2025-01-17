#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "buf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buf_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  struct Buf* buf = buf_new(buf_size);
  if (buf == nullptr) {
    return 0;
  }

  const size_t fmt_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  char* fmt = static_cast<char*>(malloc(fmt_size));
  if (fmt == nullptr) {
    buf_free(buf);
    return 0;
  }
  stream.ConsumeBytes(fmt, fmt_size);

  const size_t s_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  char* s = static_cast<char*>(malloc(s_size));
  if (s == nullptr) {
    buf_free(buf);
    free(fmt);
    return 0;
  }
  stream.ConsumeBytes(s, s_size);

  buf_prints(buf, fmt, s);

  buf_free(buf);
  free(fmt);
  free(s);
  return 0;
}