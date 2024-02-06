#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "regexp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the Reinst struct
  struct Reinst pc;
  pc.type = stream.ConsumeIntegralInRange<char>(0, 255);
  pc.u1.r = stream.ConsumeIntegralInRange<char>(0, 255);
  pc.u2.s = stream.ConsumeIntegralInRange<char*>(0, 255);

  // Initialize the Resub struct
  struct Resub out;
  out.nsub = stream.ConsumeIntegralInRange<int>(0, 255);
  for (int i = 0; i < 10; i++) {
    out.sub[i].sp = stream.ConsumeIntegralInRange<char*>(0, 255);
    out.sub[i].ep = stream.ConsumeIntegralInRange<char*>(0, 255);
  }

  // Initialize the remaining parameters
  char* sp = stream.ConsumeBytesAsString(stream.remaining_bytes()).c_str();
  char* bol = stream.ConsumeBytesAsString(stream.remaining_bytes()).c_str();
  int flags = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  match(&pc, sp, bol, flags, &out);

  return 0;
}