#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "zdict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t dict_size = stream.ConsumeIntegral<size_t>();
  const size_t samples_size = stream.ConsumeIntegral<size_t>();
  const int compression_level = stream.ConsumeIntegral<int>();
  const int selectivity_level = stream.ConsumeIntegral<int>();
  const size_t max_dict_size = stream.ConsumeIntegral<size_t>();
  const size_t max_samples_size = stream.ConsumeIntegral<size_t>();
  const size_t max_dict_limit = stream.ConsumeIntegral<size_t>();
  const size_t max_samples_limit = stream.ConsumeIntegral<size_t>();
  const size_t max_table_size = stream.ConsumeIntegral<size_t>();
  const size_t max_chain_size = stream.ConsumeIntegral<size_t>();
  const size_t max_hash_table_size = stream.ConsumeIntegral<size_t>();

  struct ZDICT_cover_params_t params = {
    max_dict_size,
    max_samples_size,
    max_dict_limit,
    max_samples_limit,
    max_table_size,
    max_chain_size,
    max_hash_table_size,
    selectivity_level,
  };

  char* dict = static_cast<char*>(malloc(dict_size));
  stream.ConsumeBytes(dict, dict_size);
  char* samples = static_cast<char*>(malloc(samples_size));
  stream.ConsumeBytes(samples, samples_size);
  size_t dict_size_out = 0;
  ZDICT_optimizeTrainFromBuffer_cover(dict, dict_size, samples, &dict_size_out,
                                             compression_level, &params);
  free(dict);
  free(samples);
  return 0;
}