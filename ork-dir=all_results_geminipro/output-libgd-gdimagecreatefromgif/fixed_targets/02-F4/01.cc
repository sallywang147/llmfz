#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "gd.h"
#include "gdfontg.h"
#include "gdfontl.h"
#include "gdfontmb.h"
#include "gdfonts.h"
#include "gdfontt.h"

extern "C" {
#include "gd_gif_in.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string bytes = stream.ConsumeRemainingBytesAsString();
  FILE *fp = fmemopen(reinterpret_cast<void *>(const_cast<char *>(bytes.c_str())),
                       bytes.size(), "r");
  gdImagePtr img = gdImageCreateFromGif(fp);
  if (img == nullptr) {
    return 0;
  }
  gdImageDestroy(img);
  fclose(fp);
  return 0;
}