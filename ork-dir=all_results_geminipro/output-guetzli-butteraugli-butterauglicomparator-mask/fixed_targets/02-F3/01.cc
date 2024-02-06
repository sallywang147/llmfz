#include <butteraugli/butteraugli_comparator.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> buffer;
  while (stream.remaining_bytes() > 0) {
    buffer.push_back(stream.ConsumeIntegral<uint8_t>());
  }
  butteraugli::ButteraugliComparator comparator;
  std::vector<float> mask_x, mask_y;
  comparator.Mask(&buffer, &mask_x, &mask_y);  // Fix: Pass the image data as the first argument
  return 0;
}