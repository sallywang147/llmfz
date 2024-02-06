#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int ldaclib_check_nlnn_shift(int smplrate_id, int nlnn_shift);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int smplrate_id = stream.ConsumeIntegral<int>();
  int nlnn_shift = stream.ConsumeIntegral<int>();

  ldaclib_check_nlnn_shift(smplrate_id, nlnn_shift);

  return 0;
}