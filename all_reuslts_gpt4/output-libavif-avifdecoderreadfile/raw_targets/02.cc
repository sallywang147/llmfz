#include <fuzzer/FuzzedDataProvider.h>
#include <avif/avif.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  avifDecoder * decoder = avifDecoderCreate();
  avifImage * image = avifImageCreateEmpty();

  std::string filename = stream.ConsumeRandomLengthString();
  
  int result = avifDecoderReadFile(decoder, image, const_cast<char *>(filename.c_str()));

  avifImageDestroy(image);
  avifDecoderDestroy(decoder);

  return 0;
}