#include <cstdio>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);

  // Extract input data
  std::vector<uint8_t> img = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024 * 1024));
  void *img_ptr = img.data();
  int nPlanes = stream.ConsumeIntegralInRange(1, 4);

  // Initialize LibRaw object
  LibRaw libRaw;

  // Call the function to fuzz
  libRaw.crxLoadDecodeLoop(&libRaw, reinterpret_cast<char *>(img_ptr), nPlanes);

  return 0;
}