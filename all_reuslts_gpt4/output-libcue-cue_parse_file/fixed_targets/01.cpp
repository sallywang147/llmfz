#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "libcue/libcue.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();

  FILE *tmpfile = fmemopen((void *)str.c_str(), str.size(), "rb");
  if (!tmpfile) {
    return 0;
  }

  struct Cd *cd = cue_parse_file(tmpfile);
  if (cd) {
    cd_delete(cd);
  }

  fclose(tmpfile);

  return 0;
}