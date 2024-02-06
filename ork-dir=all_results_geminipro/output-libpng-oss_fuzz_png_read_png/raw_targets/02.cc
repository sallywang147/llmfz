#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <png.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (png_ptr == nullptr) {
    return 0;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == nullptr) {
    png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    return 0;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
  }

  png_set_read_fn(png_ptr, nullptr, [](png_structp png_ptr, png_bytep data, png_size_t length) {
    FuzzedDataProvider* stream = static_cast<FuzzedDataProvider*>(png_get_io_ptr(png_ptr));
    const auto data_ptr = stream->ConsumeBytes<uint8_t>(length);
    std::memcpy(data, data_ptr.data(), length);
  });

  png_process_data(png_ptr, info_ptr, nullptr, 0);

  const int transforms = stream.ConsumeIntegral<int>();
  const std::string params = stream.ConsumeRemainingBytesAsString();

  OSS_FUZZ_png_read_png(png_ptr, info_ptr, transforms, const_cast<char*>(params.c_str()));

  png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

  return 0;
}