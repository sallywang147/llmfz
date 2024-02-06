#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vas.h"
#include "vdef.h"
#include "vsb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct vsb vsb[1];
  VSB_init(vsb, NULL, 0);
  
  const int len = stream.ConsumeIntegralInRange<int>(0, size);
  std::string v = stream.ConsumeBytesAsString(len);
  
  const int how = stream.ConsumeIntegral<int>();
  
  VSB_quote(vsb, v.data(), len, how);
  
  VSB_finish(vsb);
  
  return 0;
}