#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t file_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  std::vector<uint8_t> file_buffer(file_size);
  stream.ConsumeBytes<uint8_t>(file_buffer.data(), file_size);

  WavpackContext* wpc = WavpackOpenFileInput(file_buffer.data(), file_size, 0, 0);
  if (wpc == nullptr) {
    return 0;
  }
  WavpackSeekTrailingWrapper(wpc);
  WavpackCloseFile(wpc);
  return 0;
}