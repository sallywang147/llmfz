#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include "cmark.h"
#include "houdini.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct cmark_strbuf strbuf = CMARK_BUF_INIT;
  int len = stream.ConsumeIntegralInRange<int>(0, size);
  std::string str = stream.ConsumeBytesAsString(len);
  char *ptr = const_cast<char *>(str.c_str());

  houdini_escape_html(&strbuf, ptr, len);

  cmark_strbuf_free(&strbuf);

  return 0;
}