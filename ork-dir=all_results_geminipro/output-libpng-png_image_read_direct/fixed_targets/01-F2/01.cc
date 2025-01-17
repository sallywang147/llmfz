#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <png.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input_string = stream.ConsumeRemainingBytesAsString();
  png_image image;
  memset(&image, 0, sizeof(image));
  image.version = PNG_IMAGE_VERSION;
  if (png_image_read_from_memory(&image,
                                reinterpret_cast<png_bytep>(const_cast<char*>(input_string.c_str())),
                                input_string.size()) != 0) {
    return 0;
  }
  png_image_free(&image);
  return 0;
}

int main() {
  return 0;
}
```

The fixed code includes the following changes:

1. The `png_image_read_direct` function is not used in the code, so it is removed.
2. The `png_image_read_from_memory` function is used to read the PNG image data from memory.
3. The `png_image_free` function is used to free the memory allocated for the PNG image data.

With these changes, the code should now build and run successfully.