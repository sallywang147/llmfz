#include <fuzzer/FuzzedDataProvider.h>
#include <stb_image.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int x = stream.ConsumeIntegral<int>();
  int y = stream.ConsumeIntegral<int>();
  int comp = stream.ConsumeIntegral<int>();
  int req_comp = stream.ConsumeIntegral<int>();
  stbi__result_info ri;

  stbi__context s;
  stbi__start_mem(&s, data, size);

  char* result = stbi__jpeg_load(&s, &x, &y, &comp, req_comp, &ri);

  if (result != nullptr) {
    stbi_image_free(result);
  }

  return 0;
}