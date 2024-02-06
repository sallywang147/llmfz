#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "png.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  png_image image;
  memset(&image, 0, sizeof(image));

  const size_t memory_size = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> memory(memory_size);
  stream.ConsumeBytes<uint8_t>(memory.data(), memory_size);

  int result = OSS_FUZZ_png_image_begin_read_from_memory(&image,
                                                        reinterpret_cast<char*>(memory.data()),
                                                        memory_size);
  if (result == 0) {
    png_image_free(&image);
  }

  return 0;
}