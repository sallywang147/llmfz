#include <cstdio>
#include <cstring>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);

  LibRaw raw;
  char *function_name = raw.unpack_function_name(&raw);
  free(function_name);

  return 0;
}