#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <png.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize png_image structure
  struct png_image image;
  memset(&image, 0, (sizeof image));
  image.version = PNG_IMAGE_VERSION;

  // Consume data as string
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *memory = const_cast<char*>(str.c_str());

  // Call the function to fuzz
  OSS_FUZZ_png_image_begin_read_from_memory(&image, memory, str.size());

  return 0;
}