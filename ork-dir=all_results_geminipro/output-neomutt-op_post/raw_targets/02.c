#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct IndexSharedData* shared_data = new struct IndexSharedData;
  struct IndexPrivateData* private_data = new struct IndexPrivateData;
  int arg_2 = provider.ConsumeIntegral<int>();
  int ret = op_post(shared_data, private_data, arg_2);
  delete shared_data;
  delete private_data;
  return ret;
}