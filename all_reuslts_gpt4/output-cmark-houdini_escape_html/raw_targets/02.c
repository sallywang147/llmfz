#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cmark.h"
#include "houdini.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct cmark_strbuf strbuf = CMARK_BUF_INIT;
  std::string str = stream.ConsumeRandomLengthString();

  // Ensure that the length of the string does not exceed the remaining bytes in the stream
  int len = stream.remaining_bytes() < str.size() ? stream.remaining_bytes() : str.size();

  houdini_escape_html(&strbuf, str.c_str(), len);

  cmark_strbuf_free(&strbuf);

  return 0;
}