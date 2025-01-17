#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"
#include "zdict.h"

extern "C" {
#include "zdict.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t dict_size = stream.ConsumeIntegral<size_t>();
  const size_t train_size = stream.ConsumeIntegral<size_t>();
  const int compression_level = stream.ConsumeIntegralInRange<int>(-1, 9);
  const int ddict_size = stream.ConsumeIntegralInRange<int>(-1, 32);
  const int strategy = stream.ConsumeIntegralInRange<int>(0, 3);
  const int full_search = stream.ConsumeBool();
  const int content_size = stream.ConsumeIntegralInRange<int>(0, 1024);
  const int notification_level = stream.ConsumeIntegralInRange<int>(0, 3);
  const int dict_id = stream.ConsumeIntegralInRange<int>(0, 1024);
  const int reserved_value = stream.ConsumeIntegralInRange<int>(0, 1024);

  std::vector<uint8_t> dict_buffer(dict_size);
  std::vector<uint8_t> train_buffer(train_size);
  std::vector<uint8_t> result_buffer(dict_size);
  size_t result_size = dict_size;
  ZDICT_legacy_params_t params = {
      ddict_size, strategy, full_search, content_size, notification_level,
      dict_id, reserved_value};

  size_t result = ZDICT_trainFromBuffer_unsafe_legacy(
      reinterpret_cast<char*>(result_buffer.data()), &result_size,
      reinterpret_cast<char*>(train_buffer.data()), train_size,
      compression_level, &params);

  return result;
}