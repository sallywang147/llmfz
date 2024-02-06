#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <string>

#include "gd.h"
#include "gdfontg.h"
#include "gdfontl.h"
#include "gdfontmb.h"
#include "gdfonts.h"
#include "gdfontt.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  gdImagePtr slate_image = gdImageCreateFromGif(gdOpenFile(bytes.data()));
  if (slate_image == nullptr) {
    return 0;
  }
  gdImageDestroy(slate_image);
  return 0;
}