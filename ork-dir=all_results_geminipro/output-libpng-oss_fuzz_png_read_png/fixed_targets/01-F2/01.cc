#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <png.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t png_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::string png_data =
      std::string(reinterpret_cast<const char*>(stream.ConsumeBytes<uint8_t>(png_size).data()),
                  png_size);

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (png_ptr == nullptr) {
    return 0;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == nullptr) {
    png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    return 0;
  }

  png_set_read_fn(png_ptr, &png_data, [](png_structp png_ptr, png_bytep out, png_size_t length) {
    png_voidp io_ptr = png_get_io_ptr(png_ptr);
    std::string* data = static_cast<std::string*>(io_ptr);
    if (length > data->size()) {
      png_error(png_ptr, "png_read_png: Read too many bytes");
    }
    memcpy(out, data->data(), length);
    data->erase(data->begin(), data->begin() + length);
  });

  const std::string transforms = stream.ConsumeRemainingBytesAsString();
  std::ostringstream oss;
  oss << (transforms.size() ? strtol(transforms.c_str(), nullptr, 0) : 0);
  OSS_FUZZ_png_read_png(png_ptr, info_ptr, oss.str().size() ? strtol(oss.str().c_str(), nullptr, 0) : 0,
                        oss.str().size() ? const_cast<char*>(oss.str().c_str()) : nullptr, 0);

  png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
  return 0;
}