#include <brunsli/brunsli_decode.h>
#include <brunsli/types.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int quality = stream.ConsumeIntegral<int>();
  bool is_opaque = stream.ConsumeBool();
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();
  char *data_ptr = reinterpret_cast<char*>(bytes.data());
  brunsli::FindBestMatrix(&quality, is_opaque, data_ptr);
  return 0;
}