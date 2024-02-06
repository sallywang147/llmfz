#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int RegularCommandService(int *PortNumber);

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider provider(Data, Size);

  int PortNumber = provider.ConsumeIntegral<int>();
  RegularCommandService(&PortNumber);
  return 0;
}