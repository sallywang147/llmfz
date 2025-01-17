#include <cstdio>
#include <cstring>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <libraw/libraw.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int nPlanes = stream.ConsumeIntegralInRange<int>(0, 100);

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 100000));
  char *img = reinterpret_cast<char *>(bytes.data());

  // Extract to user defined object
  LibRaw obj;
  size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  // Call the function
  obj.crxLoadDecodeLoop(&obj, img, nPlanes);

  return 0;
}