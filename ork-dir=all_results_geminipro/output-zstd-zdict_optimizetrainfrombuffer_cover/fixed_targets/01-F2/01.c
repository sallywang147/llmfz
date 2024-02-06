#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zdict.h"

extern "C" {
#include "zdict.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t dict_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  std::vector<char> dict(dict_size);
  stream.ConsumeBytes(&dict[0], dict_size);

  const size_t samples_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  std::vector<char> samples(samples_size);
  stream.ConsumeBytes(&samples[0], samples_size);

  size_t dict_content_size = 0;
  std::vector<size_t> covered_dict_content_size(1);
  const int compression_level = stream.ConsumeIntegralInRange<int>(0, 10);
  struct ZDICT_cover_params_t params;
  params.k = stream.ConsumeIntegralInRange<int>(0, 10);
  params.d = stream.ConsumeIntegralInRange<int>(0, 10);
  params.steps = stream.ConsumeIntegralInRange<int>(0, 10);

  ZDICT_optimizeTrainFromBuffer_cover(&dict[0], dict_size, &samples[0],
                                    &covered_dict_content_size[0],
                                    compression_level, &params);

  return 0;
}
```

The original code had no issues.