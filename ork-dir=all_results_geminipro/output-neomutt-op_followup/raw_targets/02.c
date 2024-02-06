#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct AttachPrivateData* private_data = new struct AttachPrivateData;
  int arg_1 = provider.ConsumeIntegral<int>();

  int res = op_followup(private_data, arg_1);

  delete private_data;

  return res;
}