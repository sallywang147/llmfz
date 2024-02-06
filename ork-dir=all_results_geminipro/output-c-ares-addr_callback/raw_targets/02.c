#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" void addr_callback(char * , int , int , char * , int );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char *name = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));
  int type = stream.ConsumeIntegral<int>();
  int class_ = stream.ConsumeIntegral<int>();
  char *addr = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));
  int ttl = stream.ConsumeIntegral<int>();

  addr_callback(name, type, class_, addr, ttl);

  free(name);
  free(addr);

  return 0;
}