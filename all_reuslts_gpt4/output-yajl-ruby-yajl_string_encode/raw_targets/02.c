#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "api/yajl_buf.h"
#include "api/yajl_encode.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int len = stream.ConsumeIntegralInRange<int>(0, size);
  std::string str = stream.ConsumeBytesAsString(len);
  int htmlSafe = stream.ConsumeBool();

  yajl_buf buf = yajl_buf_alloc(NULL);
  yajl_string_encode(buf, (char *)str.c_str(), len, htmlSafe);

  yajl_buf_free(buf);

  return 0;
}