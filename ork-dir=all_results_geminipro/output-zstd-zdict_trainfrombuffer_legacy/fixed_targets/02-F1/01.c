#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "zdict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t dict_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  char* dict = new char[dict_size];
  stream.ConsumeBytes(dict, dict_size);
  const size_t train_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  char* train = new char[train_size];
  stream.ConsumeBytes(train, train_size);
  size_t train_result_size = 0;
  ZDICT_legacy_params_t params;
  memset(&params, 0, sizeof(params));
  params.compressionLevel = stream.ConsumeIntegralInRange<int>(0, 12);
  const size_t result = ZDICT_trainFromBuffer_legacy(
      dict, dict_size, train, &train_result_size, params.compressionLevel, &params);
  delete[] dict;
  delete[] train;
  return 0;
}