#include <algorithm>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
int signkey_generate(int keytype, int bits, char *filename, int skip_exist);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider data(Data, Size);
  int keytype = data.ConsumeIntegralInRange<int>(0, 4);
  int bits = data.ConsumeIntegralInRange<int>(0, 4096);
  char filename[256];
  data.ConsumeString(filename, 256);  // Fix: use ConsumeString instead of ConsumeBytesInArray
  int skip_exist = data.ConsumeBool();
  signkey_generate(keytype, bits, filename, skip_exist);
  return 0;
}