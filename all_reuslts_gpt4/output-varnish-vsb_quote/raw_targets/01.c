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
  
  struct vsb *s = VSB_new_auto();
  if (s == NULL)
    return 0;
  
  size_t len = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
  std::string v = stream.ConsumeBytesAsString(len);
  int how = stream.ConsumeIntegral<int>();
  
  VSB_quote(s, v.c_str(), len, how);
  
  VSB_delete(s);
  
  return 0;
}