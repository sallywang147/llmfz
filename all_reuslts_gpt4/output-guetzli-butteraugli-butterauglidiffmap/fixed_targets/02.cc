#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create two vectors for the first two parameters of ButteraugliDiffmap.
  std::vector<float> vector1 = stream.ConsumeBytes<float>(stream.remaining_bytes() / 2);
  std::vector<float> vector2 = stream.ConsumeRemainingBytes<float>();

  // Create an Image for the third parameter of ButteraugliDiffmap.
  butteraugli::Image image;

  // Call the target function.
  butteraugli::ButteraugliDiffmap(&vector1, &vector2, &image);

  return 0;
}