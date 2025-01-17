#include "../common/platform.h"
#include "../dec/state.h"
#include <brunsli/brunsli_decode.h>
#include <brunsli/jpeg_data.h>
#include <brunsli/jpeg_data_writer.h>
#include <brunsli/status.h>
#include <brunsli/types.h>
#include <fuzzer/FuzzedDataProvider.h>

size_t DiscardOutputFunction(void *data, const uint8_t *buf, size_t count) {
  BRUNSLI_UNUSED(data);
  BRUNSLI_UNUSED(buf);
  return count;
}

extern "C" {
#include <brunsli/brunsli_dictionary.h>
}

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int num_blocks = stream.ConsumeIntegralInRange<int>(1, 1000);
  bool is_chroma_derived = stream.ConsumeBool();
  std::vector<char> matrix(num_blocks * 6);
  stream.ConsumeBytes(matrix.data(), matrix.size());
  int result = brunsli::FindBestMatrix(matrix.data(), is_chroma_derived,
                                       matrix.data());
  BRUNSLI_UNUSED(result);
  return 0;
}