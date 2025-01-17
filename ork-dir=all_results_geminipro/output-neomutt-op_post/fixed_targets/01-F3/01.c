#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" {
#include "op.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct IndexSharedData {
    std::vector<uint8_t> data;
  };

  struct IndexPrivateData {
    std::vector<uint8_t> data;
  };

  IndexSharedData shared;
  IndexPrivateData private_data;

  int arg_int = provider.ConsumeIntegral<int>();

  op_post(&shared, &private_data, arg_int);

  return 0;
}