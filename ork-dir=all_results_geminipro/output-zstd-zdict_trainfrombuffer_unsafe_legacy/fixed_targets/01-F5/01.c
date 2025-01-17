#include <fuzzer/FuzzedDataProvider.h>
#include <zdict.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t dict_size = stream.ConsumeIntegralInRange<size_t>(0, 65536);
  char* dict = new char[dict_size];
  stream.ConsumeBytes(dict, dict_size);
  const size_t max_dict_size = stream.ConsumeIntegralInRange<size_t>(0, 65536);
  size_t dict_size_out = 0;
  const int compression_level = stream.ConsumeIntegralInRange<int>(0, 22);
  const int notification_level = stream.ConsumeIntegralInRange<int>(0, 3);
  ZDICT_legacy_params_t params;
  params.notificationLevel = notification_level;
  params.dictContentSize = dict_size;
  params.dictContentType = ZDICT_dt_rawContent;
  params.checksumFlag = 0;

  size_t ret = ZDICT_trainFromBuffer_unsafe_legacy(dict, dict_size, nullptr,
                                                  &dict_size_out,
                                                  compression_level, &params);
  delete[] dict;  // Corrected the use of `delete[]` instead of `free`.
  return 0;
}