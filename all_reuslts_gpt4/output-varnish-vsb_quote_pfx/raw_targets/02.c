#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vas.h"
#include "vsb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct vsb s;
  VSB_init(&s, NULL, 0);

  std::string pfx = stream.ConsumeRandomLengthString();
  std::string v = stream.ConsumeRemainingBytesAsString();
  int len = v.size();
  int how = stream.ConsumeIntegral<int>();

  VSB_quote_pfx(&s, (char*)pfx.c_str(), (char*)v.c_str(), len, how);

  VSB_destroy(&s);

  return 0;
}